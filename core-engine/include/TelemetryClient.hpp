// SPDX-License-Identifier: MIT
// Copyright (c) 2022 Fulvio Favilla (@fulviofavilla)

#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace aerospace {

/**
 * @class TelemetryClient
 * @brief Handles the connection and data transmission to the Telemetry Server.
 */
class TelemetryClient {
public:
    /**
     * @brief Constructor for the telemetry client.
     * @param socketPath Path to the Unix Domain Socket file.
     */
    explicit TelemetryClient(const std::string& socketPath);

    /**
     * @brief Destructor ensures the socket is closed (RAII).
     */
    ~TelemetryClient();

    // Prevent accidental copying of the connection
    TelemetryClient(const TelemetryClient&) = delete;
    TelemetryClient& operator=(const TelemetryClient&) = delete;

    /**
     * @brief Connects to the server socket at the specified path.
     * @return true if connection is successful, false otherwise.
     */
    bool connectToServer();

    /**
     * @brief Sends a telemetry packet (vector of bytes) to the server.
     * @param data The raw byte stream to send.
     * @return true if all bytes were sent, false otherwise.
     */
    bool sendTelemetry(const std::vector<uint8_t>& data);

    /**
     * @brief Closes the active socket connection.
     */
    void disconnect();

private:
    std::string path_;
    int socketFd_;
};

} // namespace aerospace
