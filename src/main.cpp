#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <string>
#include <atomic>
#include <csignal>

#include "lhig/legacy_client.hpp"
#include "lhig/opcua_server.hpp"

// Global flag for graceful shutdown on CTRL+C
std::atomic<bool> keep_running(true);

void signal_handler(int signum) {
    std::cout << "\nCaught signal " << signum << ", shutting down..." << std::endl;
    keep_running = false;
}

int main() {
    // Register signal handlers
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    std::cout << "LHIG Gateway starting up..." << std::endl;

    // 1. Config
    const char* host_env = std::getenv("DEVICE_HOST");
    const char* port_env = std::getenv("DEVICE_PORT");
    std::string host = (host_env) ? host_env : "127.0.0.1";
    int port = (port_env) ? std::atoi(port_env) : 9999;

    // 2. Initialize Components
    lhig::LegacyClient client(host, port);
    lhig::OpcuaServer server;

    // 3. Connect to Legacy Hardware
    if (!client.connect()) {
        std::cerr << "Fatal: Could not connect to legacy device." << std::endl;
        return 1;
    }
    
    // 4. Start OPC UA Server (Background Thread)
    server.start();

    // 5. Main Control Loop
    while (keep_running) {
        // A. Poll Legacy Device
        std::string response = client.sendCommand("READ:VOLT");
        std::cout << "[Control Loop] Legacy says: " << response << std::endl;

        // B. Update OPC UA Server (Future Step)
        // server.updateVoltage(...);

        // C. Sleep (Poll Rate)
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    // 6. Shutdown
    std::cout << "Shutdown initiated." << std::endl;
    server.stop();
    client.disconnect();

    std::cout << "LHIG Gateway shut down gracefully." << std::endl;
    return 0;
}