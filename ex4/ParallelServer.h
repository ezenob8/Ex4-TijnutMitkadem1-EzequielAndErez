//
// Created by erez on 22/01/2020.
//

#ifndef EX4_PARALLELSERVER_H
#define EX4_PARALLELSERVER_H

#include "IServer.h"
#include <netinet/in.h>
#include "IClientHandler.h"
using namespace server_side;
class ParallelServer : public server_side::IServer{
private:
    void open(int sock,sockaddr_in add,IClientHandler* c);
    void clientThread(int client_socket, IClientHandler* client_handler);
    bool stopLoop{};
public:
    void start(int port,IClientHandler* c) override; // openList a server
    void stop() override; // close the server
    ParallelServer()= default;;
};


#endif //EX4_PARALLELSERVER_H
