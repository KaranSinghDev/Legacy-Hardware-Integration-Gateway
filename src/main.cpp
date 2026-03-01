#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <string>
#include <atomic>
#include <csignal>

#include "lhig/legacy_client.hpp"
#include "lhig/opcua_server.hpp"

std::atomic<bool> keep_running(true);

void signal_handler(int signum) {
    keep_running = false;
}

double parseVoltage(const std::string& raw) {
    try {
        size_t colonPos = raw.find(':');
        if (colonPos != std::string::npos && colonPos + 1 < raw.length()) {
            return std::stod(raw.substr(colonPos + 1));
        }
    } catch (...) {}
    return -1.0; 
}

int main() {
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    std::cout << "LHIG Gateway starting up..." << std::endl;

    const char* host_env = std::getenv("DEVICE_HOST");
    std::string host = (host_env) ? host_env : "127.0.0.1";
    
    const char* port_env = std::getenv("DEVICE_PORT");
    int port = (port_env) ? std::atoi(port_env) : 9999;

    lhig::LegacyClient client(host, port);
    lhig::OpcuaServer server;

    // Start OPC UA Server immediately, regardless of hardware connection status
    server.start();

    // --- State-Aware Control Loop ---
    while (keep_running) {
        
        // Check State: Are we connected?
        if (!client.isConnected()) {
            std::cout << "[Gateway] Connection down. Attempting to connect..." << std::endl;
            if (!client.connect()) {
                // If it fails, wait 2 seconds and loop again
                std::this_thread::sleep_for(std::chrono::seconds(2));
                continue; 
            }
        }

        // If we reach here, we are connected. Get the data.
        std::string response = client.sendCommand("READ:VOLT");
        
        if (response == "ERR:DISCONNECTED") {
            std::cerr << "[Gateway] Connection lost during data transfer." << std::endl;
            continue; // The loop will handle reconnection on the next pass
        }

        double voltage = parseVoltage(response);

        if (voltage >= 0.0) {
             server.updateVoltage(voltage);
             std::cout << "[Gateway] Updated OPC UA Node 'Voltage' -> " << voltage << " V" << std::endl;
        } else {
             std::cerr << "[Gateway] Error parsing response: \"" << response << "\"" << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    server.stop();
    client.disconnect();
    return 0;
}