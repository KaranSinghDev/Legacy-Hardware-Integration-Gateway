
#include "lhig/legacy_client.hpp"
#include <iostream>

namespace lhig {
    //constructor
    LegacyClient::LegacyClient(const std::string& host, int port)
    : host_(host), port_(port){
        std::cout<<"LegacyClient created for"<<host_<<":"<<port_<<std::endl;
    }
    //method implementation (stubs)

    bool LegacyClient::connect(){
        std::cout<<"Connecting to legacy device"<<std::endl;
        return true;
    }
    
    void LegacyClient::disconnect(){
        std::cout<<"Disconnecting from legacy device"<<std::endl;
    }

    std::string LegacyClient::sendCommand(const std::string& command){
        std::cout<<"Sending command: "<<command<<std::endl;
        return "OK";
    }

}