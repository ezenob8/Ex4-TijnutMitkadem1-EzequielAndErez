//
// Created by erez on 19/01/2020.
//

#ifndef EX4_ISEARCHABLE_H
#define EX4_ISEARCHABLE_H

#include <vector>
#include "State.h"

using namespace std;

//interface of all the objects the we can perform serach on
template<class T>
class ISearchable {
public:
    virtual int getSize() = 0;//size of the object

    virtual State<T> *getInitialState() = 0;//from where to begin

    virtual bool isGoalState(State<T> *state) = 0;//have we reached the destination

    virtual State<T> *getGoalState() = 0;//get the goal

    virtual vector<State<T> *> *getAllPossibleStates(State<T> *state) = 0;//get all neighbours of a state
};
#endif //EX4_ISEARCHABLE_H
