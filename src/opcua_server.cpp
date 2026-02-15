#include "lhig/opcua_server.hpp"

// CRITICAL CHANGE: Modular includes
#include <open62541/server.h>
#include <open62541/server_config_default.h>

#include <iostream>

namespace lhig {

OpcuaServer::OpcuaServer() : running_(false) {
    server_ = UA_Server_new();
    // CRITICAL CHANGE: Explicitly load default configuration (Port 4840)
    UA_ServerConfig_setDefault(UA_Server_getConfig(server_));
}

OpcuaServer::~OpcuaServer() {
    stop();
    UA_Server_delete(server_);
}

void OpcuaServer::start() {
    if (running_) return;
    
    running_ = true;
    std::cout << "[OPC UA] Starting Server on opc.tcp://0.0.0.0:4840" << std::endl;
    
    server_thread_ = std::thread(&OpcuaServer::runLoop, this);
}

void OpcuaServer::stop() {
    if (!running_) return;
    
    std::cout << "[OPC UA] Stopping Server..." << std::endl;
    running_ = false;
    
    if (server_thread_.joinable()) {
        server_thread_.join();
    }
    std::cout << "[OPC UA] Server Stopped." << std::endl;
}

void OpcuaServer::runLoop() {
    UA_Server_run(server_, (volatile UA_Boolean*)&running_);
}

void OpcuaServer::updateVoltage(double voltage) {
    // Phase 3 implementation
}

} // namespace lhig