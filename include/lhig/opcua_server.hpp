#ifndef LHIG_OPCUA_SERVER_HPP
#define LHIG_OPCUA_SERVER_HPP

#include <thread>
#include <atomic>

// Forward declaration
struct UA_Server;

namespace lhig {

class OpcuaServer {
public:
    OpcuaServer();
    ~OpcuaServer();

    void start();
    void stop();

    // Placeholder for Phase 3
    void updateVoltage(double voltage);

private:
    void runLoop();

    UA_Server* server_;
    volatile bool running_; 
    std::thread server_thread_;
};

} // namespace lhig

#endif // LHIG_OPCUA_SERVER_HPP

