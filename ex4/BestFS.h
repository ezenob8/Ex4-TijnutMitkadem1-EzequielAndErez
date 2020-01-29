//
//
// Created by erez on 19/01/2020.
//

#ifndef EX4_BestFS_H
#define EX4_BestFS_H

#include "ISearcher.h"
#include "Cell.h"
#include "State.h"
#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <list>
#include <iterator>
#include <utility>
#include <stack>
#include <unordered_set>
#include "PriorityQueue.h"

using namespace std;

template<class S, class T>
class BestFS : public ISearcher<S, T> {
    State<Cell *> *initial;
    PriorityQueue<State<T> *> *openList = new PriorityQueue<State<T> *>();
    unordered_set<State<T> *> *closed = new unordered_set<State<T> *>();

    string getPath(ISearchable<T> *searchable) {
        string solution = "";
        auto *copyDst = new State<Cell *>(searchable->getGoalState());
        auto *path = new stack<string>();
        while (!copyDst->equals(searchable->getInitialState())) {
            State<Cell *> *father = copyDst->getCameFrom();
            auto *neighbours = searchable->getAllPossibleStates(copyDst);
            if (father->equals(neighbours->at(0))) { //right
                path->push("Left (" + to_string((int) copyDst->getTotalCost()) + "), ");
            } else if (father->equals(neighbours->at(1))) { //left
                path->push("Right (" + to_string((int) copyDst->getTotalCost()) + "), ");
            } else if (father->equals(neighbours->at(2))) { //up
                path->push("Down (" + to_string((int) copyDst->getTotalCost()) + "), ");
            } else if (father->equals(neighbours->at(3))) { //down
                path->push("Up (" + to_string((int) copyDst->getTotalCost()) + "), ");
            } else {
                return "NULL";
            }
            copyDst = copyDst->getCameFrom();
        }

        while (!path->empty()) {
            solution += path->top();
            path->pop();
        }
        solution = solution.substr(0, solution.length() - 2);
        return solution;
    }

public:
    BestFS() {
    }

    string search(ISearchable<T> *searchable) override {
        initial = searchable->getInitialState();
        if (initial->getCost() == -1 || searchable->getGoalState()->getCost() == -1) {
            return "source or destination are blocked cells";
        }
        openList->push(initial);
        while (!this->openList->empty()) {
            State<T> *top = this->openList->top();
            this->openList->pop();
            this->closed->insert(top);
            if (searchable->isGoalState(top)) {
                return getPath(searchable);
            }
            vector<State<T> *> *neighbours = searchable->getAllPossibleStates(top);
            for (State<T> *neighbour:*neighbours) {
                if (neighbour == NULL || neighbour->getCost() == -1) {
                    continue;
                }
                if (this->closed->find(neighbour) == this->closed->end() && !this->openList->find(neighbour)) {
                    neighbour->setParent(top);
                    this->openList->push(neighbour);
                } else if (neighbour->getTotalCost() > (top->getTotalCost() + neighbour->getCost())) {
                    int cost = top->getTotalCost() + neighbour->getCost();
                    neighbour->setCost(cost);
                    if (!this->openList->find(neighbour)) {
                        this->openList->push(neighbour);
                    } else {
                        State<T> *save = neighbour;
                        this->openList->remove(neighbour);
                        this->openList->push(save);
                    }
                }

            }
        }
        return "solution doesnt exists\r\n";
    }//end of search function

}; //end of class BestFS

#endif //EX4_BestFS_H

