#include "TelemetryClient.hpp"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

int main() {
    aerospace::TelemetryClient client("/tmp/aerospace_telemetry.sock");

    std::cout << "[Test] Attempting to connect to telemetry engine...\n";

    if (!client.connectToServer()) {
        return 1;
    }

    // Simulate sending 5 packets of telemetry
    for (int i = 1; i <= 5; ++i) {
        std::vector<uint8_t> mockData(128, 0xAB); // 128 bytes of dummy data
        if (client.sendTelemetry(mockData)) {
            std::cout << "[Test] Packet " << i << " sent successfully.\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
