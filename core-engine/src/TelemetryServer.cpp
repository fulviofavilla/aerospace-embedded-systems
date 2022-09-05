// SPDX-License-Identifier: MIT
// Copyright (c) 2022 Fulvio Favilla (@fulviofavilla)

#include "TelemetryServer.hpp"
#include <iostream>
#include <unistd.h>
#include <cstring>

namespace aerospace {

TelemetryServer::TelemetryServer(const std::string& socketPath, const std::string& logPath)
    : path_(socketPath),
      serverFd_(-1),
      clientFd_(-1),
      running_(false),
      logger_(logPath) {} // Initialize the logger with the blackbox path

TelemetryServer::~TelemetryServer() {
    cleanup();
}

bool TelemetryServer::initialize() {
    // Create Unix Domain Socket
    serverFd_ = socket(AF_UNIX, SOCK_STREAM, 0);
    if (serverFd_ < 0) {
        std::cerr << "[Server] Failed to create socket.\n";
        return false;
    }

    unlink(path_.c_str());

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, path_.c_str(), sizeof(addr.sun_path) - 1);

    if (bind(serverFd_, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cerr << "[Server] Failed to bind socket.\n";
        return false;
    }

    if (listen(serverFd_, 5) < 0) {
        std::cerr << "[Server] Failed to listen on socket.\n";
        return false;
    }

    running_ = true;
    return true;
}

void TelemetryServer::listenAndServe() {
    std::cout << "[Server] Listening for telemetry at " << path_ << "...\n";

    while (running_) {
        clientFd_ = accept(serverFd_, nullptr, nullptr);
        if (clientFd_ < 0) {
            if (running_) std::cerr << "[Server] Accept error.\n";
            continue;
        }

        std::cout << "[Server] Client connected. Processing stream...\n";
        char buffer[128];

        while (running_) {
            ssize_t bytesRead = recv(clientFd_, buffer, sizeof(buffer), 0);
            if (bytesRead <= 0) {
                std::cout << "[Server] Client disconnected or read error.\n";
                break;
            }

            // Write received data to the binary black box using the logger
            if (logger_.log(buffer, static_cast<size_t>(bytesRead))) {
                std::cout << "[Server] Logged " << bytesRead << " bytes to black box.\n";
            } else {
                std::cerr << "[Server] Critical: Failed to write to log file.\n";
            }
        }

        close(clientFd_);
        clientFd_ = -1;
    }
}

void TelemetryServer::stop() {
    running_ = false;
    cleanup();
}

void TelemetryServer::cleanup() {
    if (clientFd_ != -1) {
        close(clientFd_);
        clientFd_ = -1;
    }
    if (serverFd_ != -1) {
        close(serverFd_);
        serverFd_ = -1;
    }
    unlink(path_.c_str());
}

} // namespace aerospace
