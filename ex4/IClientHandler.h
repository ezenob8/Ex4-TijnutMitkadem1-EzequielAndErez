//
// Created by erez on 12/01/2020.
//

#ifndef EX4_ICLIENTHANDLER_H
#define EX4_ICLIENTHANDLER_H


#include <cstdio>
#include <string>
using namespace std;
//interface for client handlers
class IClientHandler {
public:
    virtual string handleClient(int socket)=0;
    virtual IClientHandler* clone()=0;
};


#endif //EX4_ICLIENTHANDLER_H
