// SPDX-License-Identifier: MIT
// Copyright (c) 2022 Fulvio Favilla (@fulviofavilla)

#pragma once

#include "TelemetryLogger.hpp"
#include <string>
#include <sys/socket.h>
#include <sys/un.h>

namespace aerospace {

/**
 * @class TelemetryServer
 * @brief Handles Unix Domain Socket connections to receive telemetry stream.
 */
class TelemetryServer {
public:
    explicit TelemetryServer(const std::string& socketPath, const std::string& logPath);
    ~TelemetryServer();

    // Prevent accidental copying of file descriptors (RAII)
    TelemetryServer(const TelemetryServer&) = delete;
    TelemetryServer& operator=(const TelemetryServer&) = delete;

    /**
     * @brief Initializes the socket, binds to the path and starts listening.
     * @return true if successful, false otherwise.
     */
    bool initialize();

    /**
     * @brief Main loop that accepts clients and processes incoming data.
     */
    void listenAndServe();

    /**
     * @brief Signals the server to stop and performs cleanup.
     */
    void stop();

private:
    std::string path_;
    int serverFd_;
    int clientFd_;
    bool running_;

    TelemetryLogger logger_;

    void cleanup();
};

} // namespace aerospace
