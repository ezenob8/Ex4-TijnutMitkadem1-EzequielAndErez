//
// Created by erez on 19/01/2020.
//

#ifndef EX4_STATE_H
#define EX4_STATE_H

#include <cstring>

//represents state of a cell in the matrix
template<class T>
class State {
private:
    T state;//the state represented by a string
    double cost;//cost to reach this state
    State<T> *cameFrom;
    double totalCost;//cost so far
public:
    //constructor
    State<T>(T state1) {
        this->state = state1;
        this->cameFrom = NULL;

    }

    //copy constructor
    State<T>(State<T> *state1) {
        this->state = state1->getState();
        this->cameFrom = state1->getCameFrom();
        this->cost = state1->getCost();
        this->totalCost = state1->getTotalCost();
    }

    //get total cost
    double getTotalCost() {
        if (this->cameFrom == nullptr) {
            return this->cost;
        }
        this->totalCost = this->cost + this->cameFrom->getTotalCost();
        return this->totalCost;
    }

    //set total cost
    void setTotalCost(double cost1) {
        this->totalCost = cost1;
    }

    double getCost() {
        return this->cost;
    }

    void setCost(double cost1) {
        this->cost = cost1;
    }

    //return father
    State<T> *getCameFrom() {
        return this->cameFrom;
    }

    void setParent(State *state1) {
        this->cameFrom = state1;
    }

    T &getState() {
        return this->state;
    }

    //is this state equals to another state
    bool equals(State<T> *state1) {
        if (state1 == NULL) {
            return false;
        }
        return this->state == state1->getState();
    }

};

#endif //EX4_STATE_H
