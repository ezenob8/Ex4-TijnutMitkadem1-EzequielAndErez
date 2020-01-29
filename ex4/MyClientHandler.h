//
// Created by erez on 12/01/2020.
//

#ifndef EX4_MYCLIENTHANDLER_H
#define EX4_MYCLIENTHANDLER_H


#include "ISolver.h"
#include "ICacheManager.h"
#include "IClientHandler.h"
#include "string"
#include "OA.h"

using namespace std;

class MyClientHandler : public IClientHandler {
private:
    ISolver<string, string> *solver;
    ICacheManager<string, string> *cm;
public:
    explicit MyClientHandler(ICacheManager<string, string> *cacheManager);

    //create a clone of client handler
    IClientHandler *clone() override;

    //handle client and solve his problem
    string handleClient(int socket) override;
};


#endif //EX4_MYCLIENTHANDLER_H
