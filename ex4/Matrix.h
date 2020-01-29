//
// Created by erez on 19/01/2020.
//

#ifndef EX4_MATRIX_H
#define EX4_MATRIX_H


#include "ISearchable.h"
#include "State.h"
#include "Cell.h"
#include <list>
#include <string>

using namespace std;

//matri xto perform search on
class Matrix : public ISearchable<Cell *> {
private:
    int **mat;//int marix
    State<Cell *> *goal;//goal state
    State<Cell *> *initial;//initial state
    int size;//size of matrix
    vector<vector<State<Cell *> *> *> *states;//vectors states
public:
    //set goal state
    void setGoal(State<Cell *> *state);
    //set start state
    void setStart(State<Cell *> *state);

    //constructor of matrix
    explicit Matrix(int size, const string &problem);

    //get start state
    State<Cell *> *getInitialState() override;

    //have we reached the goal
    bool isGoalState(State<Cell *> *state) override;

    //get neighbours
    vector<State<Cell *> *> *getAllPossibleStates(State<Cell *> *state) override;

    //get goal state
    State<Cell *> *getGoalState() override;

    //get size of matrix
    int getSize() override;
};

#endif //EX4_MATRIX_H
