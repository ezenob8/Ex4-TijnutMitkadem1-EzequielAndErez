//
// Created by erez on 12/01/2020.
//

#ifndef EX4_ISERVER_H
#define EX4_ISERVER_H

#include <netinet/in.h>
#include "IClientHandler.h"
//server interface
namespace server_side {
    class IServer {
    public:
        virtual void start(int port,IClientHandler* handler) = 0;
        virtual void stop() = 0;

    };
}
#endif //EX4_ISERVER_H
