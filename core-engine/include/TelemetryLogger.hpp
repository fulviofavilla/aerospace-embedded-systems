// SPDX-License-Identifier: MIT
// Copyright (c) 2022 Fulvio Favilla (@fulviofavilla)

#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <cstdint>
#include <mutex>

namespace aerospace {

/**
 * @class TelemetryLogger
 * @brief Handles persistent storage of telemetry packets (Flight Black Box).
 */
class TelemetryLogger {
public:
    explicit TelemetryLogger(const std::string& filename);
    ~TelemetryLogger();

    /**
     * @brief Writes raw bytes to the log file.
     * @param data Vector containing the telemetry packet.
     * @return true if write was successful.
     */
    bool log(const char* data, size_t size);

private:
    std::string filename_;
    std::ofstream fileStream_;
    std::mutex logMutex_; // Ensures thread-safety if multiple clients connect
};

} // namespace aerospace
