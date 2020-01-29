//
// Created by erez on 12/01/2020.
//

#ifndef EX4_SERIALSERVER_H
#define EX4_SERIALSERVER_H

#include "IServer.h"

class SerialServer: public server_side::IServer {
private:
    bool to_stop;
public:
    SerialServer();
    ~SerialServer();
    void start(int port, IClientHandler* handler) override;
    void stop() override;
};


#endif //EX4_SERIALSERVER_H
