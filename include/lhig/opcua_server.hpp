#ifndef LHIG_OPCUA_SERVER_HPP
#define LHIG_OPCUA_SERVER_HPP

#include <thread>
#include <atomic>
#include <open62541/types.h> // Include for UA_NodeId

struct UA_Server; // Forward declaration

namespace lhig {

class OpcuaServer {
public:
    OpcuaServer();
    ~OpcuaServer();

    void start();
    void stop();
    void updateVoltage(double voltage);

private:
    void runLoop();
    void createVoltageNode();

    UA_Server* server_;
    volatile bool running_; 
    std::thread server_thread_;
    UA_NodeId voltageNodeId_;
};

} // namespace lhig

#endif // LHIG_OPCUA_SERVER_HPP