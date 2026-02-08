#include "lhig/opcua_server.hpp"
#include <iostream>

namespace lhig{
    //constructor
    OpcuaServer::OpcuaServer(){
        std::cout<<"OpcuaServer created"<<std::endl;

    }

    //method implementaion (stubs)
    void OpcuaServer::start(){
        std::cout<<"Starting OPC UA server"<<std::endl;
    }
    void OpcuaServer::stop(){
        std::cout<<"Stopping OPC UA server"<<std::endl;
    }
}