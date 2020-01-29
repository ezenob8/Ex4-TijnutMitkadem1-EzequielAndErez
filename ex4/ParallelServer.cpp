//
// Created by erez on 22/01/2020.
//

#include <thread>
#include <iostream>
#include <unistd.h>
#include "ParallelServer.h"

void ParallelServer::start(int port, IClientHandler *c) {
    this->stopLoop = false;
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
    }
    //bind socket to IP address
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(port);

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
        throw "Could not bind the socket to an IP";
    }
    thread acceptClients(&ParallelServer::open, this, socketfd, address, c);
    acceptClients.join();
}

void ParallelServer::open(int socketfd, sockaddr_in address, IClientHandler *client_handler) {
    fd_set rset;
    FD_ZERO(&rset);
    while (!this->stopLoop) {
        //making socket listen to the port
        if (listen(socketfd, 10) == -1) {
            std::cerr << "Error during listening" << std::endl;
        }
        //setting server timeout
        struct timeval tv;
        tv.tv_sec = 1200;
        tv.tv_usec = 0;
        FD_SET(socketfd, &rset);
        int ready = select(10, &rset, NULL, NULL, &tv);
        setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &tv, sizeof tv);
        int client_socket;
        if (FD_ISSET(socketfd, &rset)) {
            client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);
            cout << "client excepted" << endl;
            thread newClient(&ParallelServer::clientThread, this, client_socket, client_handler);
            newClient.detach();//let thread run with no connection of other threads
        } else {
            close(socketfd); // closing the server socket.
            throw runtime_error("server timed out");
        }
    }
}

void ParallelServer::stop() {
    this->stopLoop = true;
}

void ParallelServer::clientThread(int client_socket, IClientHandler *client_handler) {
    IClientHandler *c = client_handler->clone();
    string sol = c->handleClient(client_socket);
    int sent = send(client_socket, sol.c_str(), sol.length(), 0);
    if (sent == -1) {
        cout << "Writing Error" << endl;
    }
    close(client_socket);
}