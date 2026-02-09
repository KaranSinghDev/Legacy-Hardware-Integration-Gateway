#include "lhig/opcua_server.hpp"
#include "open62541.h" 
#include <iostream>

namespace lhig {

OpcuaServer::OpcuaServer() : running_(false) {
    server_ = UA_Server_new();
    // We could add configuration here later
}

OpcuaServer::~OpcuaServer() {
    stop();
    UA_Server_delete(server_);
}

void OpcuaServer::start() {
    if (running_) return;
    running_ = true;
    // The server runs in its own thread so it doesn't block our main loop
    server_thread_ = std::thread(&OpcuaServer::runLoop, this);
    std::cout << "[OPC UA] Server started." << std::endl;
}

void OpcuaServer::stop() {
    if (!running_) return;
    running_ = false;
    if (server_thread_.joinable()) {
        server_thread_.join();
    }
    std::cout << "[OPC UA] Server stopped." << std::endl;
}

// This is the core server loop
void OpcuaServer::runLoop() {
    UA_Server_run(server_, &running_);
}

// This function is how we will update the value on the server
void OpcuaServer::updateVoltage(double voltage) {
    // I have to Implement the logic to create and update the voltage node.
    
}

} // namespace lhig