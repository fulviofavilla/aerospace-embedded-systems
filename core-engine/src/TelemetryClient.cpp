// SPDX-License-Identifier: MIT
// Copyright (c) 2022 Fulvio Favilla (@fulviofavilla)

#include "TelemetryClient.hpp"
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

namespace aerospace {

TelemetryClient::TelemetryClient(const std::string& socketPath)
    : path_(socketPath), socketFd_(-1) {}

TelemetryClient::~TelemetryClient() {
    disconnect();
}

bool TelemetryClient::connectToServer() {
    socketFd_ = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socketFd_ < 0) {
        std::cerr << "[Client] Failed to create socket.\n";
        return false;
    }

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, path_.c_str(), sizeof(addr.sun_path) - 1);

    if (connect(socketFd_, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cerr << "[Client] Connection failed. Is the server running?\n";
        return false;
    }

    return true;
}

bool TelemetryClient::sendTelemetry(const std::vector<uint8_t>& data) {
    if (socketFd_ < 0) return false;

    ssize_t bytesSent = send(socketFd_, data.data(), data.size(), 0);
    return bytesSent == static_cast<ssize_t>(data.size());
}

void TelemetryClient::disconnect() {
    if (socketFd_ != -1) {
        close(socketFd_);
        socketFd_ = -1;
    }
}

} // namespace aerospace
