#ifndef LHIG_LEGACY_CLIENT_HPP
#define LHIG_LEGACY_CLEINT_HPP

#include <string>

namespace lhig{

    class LegacyClient{
        public:
        //Constructor
        LegacyClient(const std::string& host, int port);
        //methods
        bool connect();
        void disconnect();
        std::string sendCommand(const std::string& command);

        private:
        // member var
        std::string host_;
        int port_;
        // socket variable is to be added
    
    };

}

#endif 