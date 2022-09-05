// SPDX-License-Identifier: MIT
// Copyright (c) 2022 Fulvio Favilla (@fulviofavilla)

#include "TelemetryLogger.hpp"
#include <iostream>
#include <chrono>
#include <iomanip>

namespace aerospace {

TelemetryLogger::TelemetryLogger(const std::string& filename) : filename_(filename) {
    // Open in append and binary mode
    fileStream_.open(filename_, std::ios::app | std::ios::binary);
    if (!fileStream_.is_open()) {
        std::cerr << "[Logger] Failed to open log file: " << filename_ << std::endl;
    }
}

TelemetryLogger::~TelemetryLogger() {
    if (fileStream_.is_open()) {
        fileStream_.close();
    }
}

bool TelemetryLogger::log(const char* data, size_t size) {
    std::lock_guard<std::mutex> lock(logMutex_);

    if (!fileStream_.is_open()) return false;

    // Write raw binary data
    fileStream_.write(data, size);

    // Optional: Flush to ensure data is saved even if power fails
    fileStream_.flush();

    return !fileStream_.fail();
}

} // namespace aerospace
