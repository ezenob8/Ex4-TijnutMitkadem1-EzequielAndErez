//
// Created by erez on 19/01/2020.
//

#include "Matrix.h"
#include <list>

//constructor of the matrix
Matrix::Matrix(int size1, const string &problem) {
    this->states = new vector<vector<State<Cell *> *> *>();
    this->size = size1;
    //creating the matrix
    this->mat = new int *[size];
    for (int i = 0; i < size; ++i) {
        this->mat[i] = new int[size];
    }

    int row = 0, col = 0, value = 0;
    string num = "";
    char *copy = (char *) malloc(problem.length() * sizeof(char));
    sprintf(copy, "%s", problem.c_str());
    char *token;
    token = strtok(copy, "\r\n");
    int countSize = 0;
    while (token != NULL && countSize != size1) {
        for (int i = 0; i < strlen(token); ++i) {
            if (token[i] == ',') {
                value = stoi(num);
                mat[row][col] = value;
                col++;
                num = "";
            } else {
                num += token[i];
            }
        }
        value = stoi(num);
        mat[row][col] = value;
        col = 0;
        num = "";
        row++;
        countSize++;
        token = strtok(NULL, "\r\n");
    }

    //now creating initial and goal
    int initialX = 0;
    int initialY = 0;
    int goalX = 0;
    int goalY = 0;
    int i;
    for (i = 0; i < strlen(token); ++i) {
        if (token[i] == ',') {
            initialX = stoi(num);
            num = "";
        } else {
            num += token[i];
        }
    }
    initialY = stoi(num);
    num = "";
    token = strtok(NULL, "\r\n");
    for (i = 0; i < strlen(token); ++i) {
        if (token[i] == ',') {
            goalX = stoi(num);
            num = "";
        } else {
            num += token[i];
        }
    }
    goalY = stoi(num);

    for (int k = 0; k < size; ++k) {
        auto *v = new vector<State<Cell *> *>();
        this->states->push_back(v);
        for (int i = 0; i < size; ++i) {
            auto *state = new State<Cell *>(new Cell(k, i));
            state->setCost(mat[k][i]);
            states->at(k)->push_back(state);
        }
    }
    this->initial = this->states->at(initialX)->at(initialY);//initialize initial
    this->goal = this->states->at(goalX)->at(goalY);//initialize initial
}

State<Cell *> *Matrix::getGoalState() {
    return this->goal;
}

bool Matrix::isGoalState(State<Cell *> *state) {
    return this->goal->equals(state);
}

State<Cell *> *Matrix::getInitialState() {
    return this->initial;
}

//return the neighbours of a cell
vector<State<Cell *> *> *Matrix::getAllPossibleStates(State<Cell *> *state) {
    Cell *c = state->getState();
    int row = c->getRow();
    int col = c->getCol();

    auto *neighbours = new vector<State<Cell *> *>();
    if (row == 0) {
        //up left corner
        if (col == 0) {
            neighbours->push_back(this->states->at(row)->at(col + 1)); //right
            neighbours->push_back(NULL);                                  //left
            neighbours->push_back(NULL);                                  //up
            neighbours->push_back(this->states->at(row + 1)->at(col)); //down
        } else if (col == size - 1) {//up right corner
            neighbours->push_back(NULL);                                    //right
            neighbours->push_back(this->states->at(row)->at(col - 1));  //left
            neighbours->push_back(NULL);                                   //up
            neighbours->push_back(this->states->at(row + 1)->at(col)); //down
        } else {
            neighbours->push_back(this->states->at(row)->at(col + 1)); //right
            neighbours->push_back(this->states->at(row)->at(col - 1)); //left
            neighbours->push_back(NULL);                                  //up
            neighbours->push_back(this->states->at(row + 1)->at(col)); //down
        }
    } else if (col == 0) {
        //down left corner
        if (row == size - 1) {
            neighbours->push_back(this->states->at(row)->at(col + 1));  //right
            neighbours->push_back(NULL);                                   //left
            neighbours->push_back(this->states->at(row - 1)->at(col)); //up
            neighbours->push_back(NULL);                                  //down
        } else {
            neighbours->push_back(this->states->at(row)->at(col + 1)); //right
            neighbours->push_back(NULL);                                  //left
            neighbours->push_back(this->states->at(row - 1)->at(col)); //up
            neighbours->push_back(this->states->at(row + 1)->at(col)); //down
        }
    } else if (row == size - 1) {
        if (col == size - 1) {//down right corner
            neighbours->push_back(NULL);                                   //right
            neighbours->push_back(this->states->at(row)->at(col - 1)); //left
            neighbours->push_back(this->states->at(row - 1)->at(col)); //up
            neighbours->push_back(NULL);                                  //down
        } else {
            neighbours->push_back(this->states->at(row)->at(col + 1)); //right
            neighbours->push_back(this->states->at(row)->at(col - 1)); //left
            neighbours->push_back(this->states->at(row - 1)->at(col)); //up
            neighbours->push_back(NULL);                                  //down
        }
    } else if (col == size - 1) {
        neighbours->push_back(NULL);                                   //right
        neighbours->push_back(this->states->at(row)->at(col - 1)); //left
        neighbours->push_back(this->states->at(row - 1)->at(col)); //up
        neighbours->push_back(this->states->at(row + 1)->at(col)); //down
    } else {
        neighbours->push_back(this->states->at(row)->at(col + 1)); //right
        neighbours->push_back(this->states->at(row)->at(col - 1)); //left
        neighbours->push_back(this->states->at(row - 1)->at(col)); //up
        neighbours->push_back(this->states->at(row + 1)->at(col)); //down
    }
    return neighbours;
}

void Matrix::setGoal(State<Cell *> *state) {
    this->goal = state;
    this->goal->setCost(state->getCost());
}

void Matrix::setStart(State<Cell *> *state) {
    this->initial = state;
}

int Matrix::getSize() {
    return this->size;
}






