#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <string>
#include <atomic>
#include <csignal>

#include "lhig/legacy_client.hpp"
#include "lhig/opcua_server.hpp"

// Global flag to handle CTRL+C gracefully
std::atomic<bool> keep_running(true);

void signal_handler(int signum) {
    std::cout << "\nCaught signal " << signum << ", shutting down..." << std::endl;
    keep_running = false;
}

int main() {
    // Register signal handler for CTRL+C
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    std::cout << "LHIG Gateway starting up..." << std::endl;

    const char* host_env = std::getenv("DEVICE_HOST");
    const char* port_env = std::getenv("DEVICE_PORT");
    std::string host = (host_env) ? host_env : "127.0.0.1";
    int port = (port_env) ? std::atoi(port_env) : 9999;

    lhig::LegacyClient client(host, port);
    lhig::OpcuaServer server;

    if (!client.connect()) {
        std::cerr << "Fatal: Could not connect to legacy device." << std::endl;
        return 1;
    }
    
    // Start the OPC UA server in the background
    server.start();

    // --- Main Control Loop ---
    while (keep_running) {
        std::string response = client.sendCommand("READ:VOLT");
        std::cout << "[Control Loop] Received: " << response << std::endl;

        // remaining: Parse the response and call server.updateVoltage()

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    std::cout << "Shutdown initiated." << std::endl;
    server.stop();
    client.disconnect();

    std::cout << "LHIG Gateway shut down gracefully." << std::endl;
    return 0;
}