// SPDX-License-Identifier: MIT
// Copyright (c) 2022 Fulvio Favilla (@fulviofavilla)

#include "TelemetryServer.hpp"
#include <iostream>
#include <csignal>

// Declare the global pointer for signal handling
aerospace::TelemetryServer* globalServer = nullptr;

/**
 * @brief Signal handler to ensure graceful shutdown on Ctrl+C (SIGINT)
 */
void handleSignal(int signum) {
    std::cout << "\n[System] Signal " << signum << " received. Shutting down telemetry engine...\n";
    if (globalServer) {
        globalServer->stop();
    }
    // No exit(signum) needed here if we want a clean return,
    // but common in CLI tools to terminate immediately.
    exit(signum);
}

int main() {
    // Register OS signals for graceful termination
    signal(SIGINT, handleSignal);
    signal(SIGTERM, handleSignal);

    const std::string SOCKET_PATH = "/tmp/aerospace_telemetry.sock";
    const std::string LOG_PATH = "flight_blackbox.bin";

    // Instantiate the server as a stack object (RAII)
    aerospace::TelemetryServer server(SOCKET_PATH, LOG_PATH);

    // Assign the address to the global pointer for the signal handler
    globalServer = &server;

    if (!server.initialize()) {
        std::cerr << "[System] Fatal: Failed to initialize telemetry server.\n";
        return 1;
    }

    // Blocking call to handle telemetry stream
    server.listenAndServe();

    return 0;
}
