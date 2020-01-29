//
// Created by erez on 12/01/2020.
//
#include "SerialServer.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <thread>

#define TIME_OUT_FIRST 30
#define TIME_OUT 10

using namespace std;

// the following method will activate the client handler over the current connected client
void activateClientHandler(bool *stop, int *sock, void *cli, socklen_t *clil, IClientHandler *clientHandler) {
    struct sockaddr cli1 = *((struct sockaddr *) cli);
    socklen_t clil1 = *clil;
    int sock1 = *sock;
    struct timeval tv;
    tv.tv_sec = TIME_OUT;
    tv.tv_usec = 0;
    // while we should not close the Server - run the loop
    while (*(stop)) {
        // try to accpet
        int client_socket = accept(sock1, (struct sockaddr *) &cli1, &clil1);
        if (client_socket < 0) {
            std::cout << ("ERROR on accept, the TIME IS OUT") << std::endl;
            return;
        }
        // calling the client handler
        cout << "acceptClient" << endl;
        string sol = clientHandler->handleClient(client_socket);
        cout << "end with client" << endl;
        int sent = send(client_socket, sol.c_str(), sol.length(), 0);
        if (sent == -1) {
            cout << "Writing Error...." << endl;
        }
        close(client_socket);
        setsockopt(*sock, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);
    }
    close(sock1);
}


void SerialServer::start(int port, IClientHandler *handler) {
    int sockfd, newsockfd;
    socklen_t clilen;
    char buffer[1024];
    struct sockaddr_in cli_addr;
    int n;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cout << ("ERROR opening socket") << std::endl;
    }
    // verify all the data is zero at the beginning
    //bzero((char *) &serv_addr, sizeof(serv_addr));
    // set the fields of sockaddr_in struct
    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    // binding stage:
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) == -1)
        std::cout << ("ERROR on binding") << std::endl;
    // create a struct for the timeout of the client's waiting
    struct timeval tv;
    tv.tv_sec = TIME_OUT_FIRST;
    tv.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);
    listen(sockfd, 5);
    cout << "server is now listening" << endl;
    clilen = sizeof(cli_addr);
    this->to_stop = true;
    bool *stopperPtr = &this->to_stop;
    int *sockfdPtr = &sockfd;
    struct sockaddr_in *client_addrPtr = &cli_addr;
    socklen_t *clilenPtr = &clilen;
    // create a new thread that will run the
    thread t1(activateClientHandler, stopperPtr, sockfdPtr, client_addrPtr, clilenPtr, handler);
    this_thread::sleep_for(std::chrono::seconds(1));
    t1.join();
}

void SerialServer::stop() {
    this->to_stop = false;
}

SerialServer::SerialServer() {

}

SerialServer::~SerialServer() = default;
