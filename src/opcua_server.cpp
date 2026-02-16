#include "lhig/opcua_server.hpp"
#include <open62541/server.h>
#include <open62541/server_config_default.h>
#include <iostream>

namespace lhig {

OpcuaServer::OpcuaServer() : running_(false) {
    server_ = UA_Server_new();
    UA_ServerConfig_setDefault(UA_Server_getConfig(server_));
    voltageNodeId_ = UA_NODEID_NULL;
}

OpcuaServer::~OpcuaServer() {
    stop();
    UA_Server_delete(server_);
}

void OpcuaServer::start() {
    if (running_) return;
    
    createVoltageNode();
    running_ = true;
    std::cout << "[OPC UA] Starting Server on opc.tcp://0.0.0.0:4840" << std::endl;
    server_thread_ = std::thread(&OpcuaServer::runLoop, this);
}

void OpcuaServer::stop() {
    if (!running_) return;
    std::cout << "[OPC UA] Stopping Server..." << std::endl;
    running_ = false;
    if (server_thread_.joinable()) server_thread_.join();
    std::cout << "[OPC UA] Server Stopped." << std::endl;
}

void OpcuaServer::runLoop() {
    UA_Server_run(server_, (volatile UA_Boolean*)&running_);
}

void OpcuaServer::createVoltageNode() {
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    UA_Double initialValue = 0.0;
    UA_Variant_setScalar(&attr.value, &initialValue, &UA_TYPES[UA_TYPES_DOUBLE]);
    attr.description = UA_LOCALIZEDTEXT("en-US", "Power Supply Voltage");
    attr.displayName = UA_LOCALIZEDTEXT("en-US", "Voltage");
    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_QualifiedName browseName = UA_QUALIFIEDNAME(1, "Voltage");
    UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);
    UA_NodeId requestedNodeId = UA_NODEID_STRING(1, "Voltage");

    UA_Server_addVariableNode(server_, requestedNodeId, parentNodeId,
                              parentReferenceNodeId, browseName,
                              variableTypeNodeId, attr, NULL, &voltageNodeId_);
                              
    std::cout << "[OPC UA] Created 'Voltage' Node." << std::endl;
}

void OpcuaServer::updateVoltage(double voltage) {
    if (UA_NodeId_isNull(&voltageNodeId_)) return;
    UA_Variant value;
    UA_Variant_setScalar(&value, &voltage, &UA_TYPES[UA_TYPES_DOUBLE]);
    UA_Server_writeValue(server_, voltageNodeId_, value);
}

} // namespace lhig