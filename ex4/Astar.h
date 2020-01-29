//
// Created by erez on 24/01/2020.
//

#ifndef EX4_ASTAR_H
#define EX4_ASTAR_H

#include "ISearcher.h"
#include "PriorityQueue.h"
#include <map>
#include <list>
#include <unordered_set>

using namespace std;

template<class S, class T>
class Astar : public ISearcher<string, T> {
private:
    State<T> *goal;
    State<T> *initial;
    PriorityQueue<State<T> *> *openList = new PriorityQueue<State<T> *>();
    unordered_set<State<T> *> *closed;
    map<State<T> *, int> gscore;
    map<State<T> *, int> fscore;

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

    double HiuristicDis(State<Cell *> *state) {
        double x = abs(this->goal->getState()->getCol() - state->getState()->getCol());
        double y = abs(this->goal->getState()->getRow() - state->getState()->getRow());
        return x + y;
    }

public:
    string search(ISearchable<T> *searchable) {
        this->initial = searchable->getInitialState();
        if(initial->getCost()==-1 || searchable->getGoalState()->getCost()==-1){
            return "source or destination are blocked";
        }
        this->goal = searchable->getGoalState();
        this->gscore.insert({initial, 0});
        this->fscore.insert({initial, HiuristicDis(initial)});
        this->closed = new unordered_set<State<T> *>();
        this->openList->push(initial);
        while (!this->openList->empty()) {
            State<T> *current = this->openList->top();
            this->openList->pop();
            if (searchable->isGoalState(current)) {
                return getPath(searchable);
            }

            this->closed->insert(current);
            vector<State<T> *> *l = searchable->getAllPossibleStates(current);
            for (State<T> *neighbour:*l) {
                if (neighbour == NULL || neighbour->getCost() == -1) {
                    continue;
                }
                if (this->closed->find(neighbour) != this->closed->end()) {
                    continue;
                }

                int cost = this->gscore[current] + neighbour->getCost();
                if (this->gscore.find(neighbour) != this->gscore.end()) {
                    if (cost < this->gscore[neighbour]) {
                        neighbour->setParent(current);
                        neighbour->setTotalCost(neighbour->getCost() + current->getTotalCost());
                        this->gscore.insert({neighbour, cost});
                        int fvalue = this->gscore[neighbour] + this->HiuristicDis(neighbour);
                        this->fscore.insert({neighbour, fvalue});
                        if (this->closed->find(neighbour) == this->closed->end()) {
                            this->closed->insert(neighbour);
                        }
                    }
                } else {
                    neighbour->setParent(current);
                    neighbour->setTotalCost(neighbour->getCost() + current->getTotalCost());
                    this->gscore.insert({neighbour, cost});
                    int fvalue = this->gscore[neighbour] + this->HiuristicDis(neighbour);
                    this->fscore.insert({neighbour, fvalue});
                    if (this->closed->find(neighbour) == this->closed->end()) {
                        this->closed->insert(neighbour);
                    }
                }
                if (!this->openList->find(neighbour)) {
                    this->openList->push(neighbour);
                }
            }
        }
        return "solution doesnt exists\r\n";
    }
};


#endif //EX4_ASTAR_H
