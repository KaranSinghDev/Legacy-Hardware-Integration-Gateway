#ifndef LHIG_LEGACY_CLIENT_HPP
#define LHIG_LEGACY_CLIENT_HPP

#include <string>

namespace lhig {

class LegacyClient {
public:
    LegacyClient(const std::string& host, int port);
    ~LegacyClient(); 

    bool connect();
    void disconnect();
    std::string sendCommand(const std::string& command);
    
    // NEW: Allow main loop to check connection state
    bool isConnected() const;

private:
    std::string host_;
    int port_;
    int sock_fd_; 
    bool is_connected_;
};

} // namespace lhig

#endif // LHIG_LEGACY_CLIENT_HPP