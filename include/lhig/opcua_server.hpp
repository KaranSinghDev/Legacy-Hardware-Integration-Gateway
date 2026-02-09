#ifndef LHIG_OPCUA_SERVER_HPP
#define LHIG_OPCUA_SERVER_HPP

#include <atomic>
#include <thread>

// Forward declare the C struct to avoid including the C header here
struct UA_Server;

namespace lhig {

class OpcuaServer {
public:
    OpcuaServer();
    ~OpcuaServer();

    void start();
    void stop();

    // This is the API our main loop will use to push data
    void updateVoltage(double voltage);

private:
    void runLoop();

    UA_Server* server_;
    std::atomic<bool> running_;
    std::thread server_thread_;
};

} 

#endif