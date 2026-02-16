#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <string> // <--- THIS WAS THE MISSING LINE
#include <atomic>
#include <csignal>

#include "lhig/legacy_client.hpp"
#include "lhig/opcua_server.hpp"

std::atomic<bool> keep_running(true);

void signal_handler(int signum) {
    keep_running = false;
}

// Helper: Parse "VOLT:5.00" -> 5.00
double parseVoltage(const std::string& raw) {
    try {
        size_t colonPos = raw.find(':');
        if (colonPos != std::string::npos && colonPos + 1 < raw.length()) {
            std::string valStr = raw.substr(colonPos + 1);
            return std::stod(valStr);
        }
    } catch (...) {
        // In production, we would log a parsing error here
    }
    return -1.0; // Error value
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

    if (!client.connect()) {
        std::cerr << "Fatal: Could not connect to legacy device." << std::endl;
        return 1;
    }
    
    server.start();

    while (keep_running) {
        std::string response = client.sendCommand("READ:VOLT");
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