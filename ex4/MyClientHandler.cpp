//
// Created by erez on 12/01/2020.
//

#include <unistd.h>
#include <cstring>
#include "MyClientHandler.h"
#include <string>
#include "DFS.h"
#include "BFS.h"
#include "BestFS.h"
#include "Astar.h"
using namespace std;

string MyClientHandler::handleClient(int socket) {
    char buffer[1024];
    string problem = "";

    //reading the problem from the client
    read(socket, buffer, 1024);
    while (!strstr(buffer, "end")) {
        problem += buffer;
        memset(buffer,0, sizeof(buffer));
        read(socket, buffer, 1024);
    }
    string solution = "";
    //if we have a solution in cache in O(1) cost
    if (cm->isSolutionExists(problem)) {
        solution = cm->get(problem);//get the solution from cache
    } else {
        //no solution in cache
        this->solver = new OA(new Astar<string, Cell *>());
        solution = solver->solve(problem);//solve the problem with Astar algorithm
        this->cm->insert(problem, solution);//insert the problem and solution to cache
    }
    return solution; //return the solution to client
}

MyClientHandler::MyClientHandler(ICacheManager<string, string> *cacheManager) {
    this->cm = cacheManager;
}

IClientHandler *MyClientHandler::clone() {
    IClientHandler *clientHandler = new MyClientHandler(this->cm);
    return clientHandler;
}
