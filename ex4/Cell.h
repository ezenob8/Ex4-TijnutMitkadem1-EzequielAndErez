//
// Created by erez on 21/01/2020.
//

#ifndef EX4_CELL_H
#define EX4_CELL_H

#include <string>
#include "State.h"

using namespace std;

class Cell {
private:
    int value;
    int row;
    int col;
public:
    Cell(int row1, int col1) {
        this->row = row1;
        this->col = col1;
    }

    int getValue() {
        return this->value;
    }

    void setValue(int val) {
        this->value = val;
    }

    int getRow() {
        return this->row;
    }

    int getCol() {
        return this->col;
    }

    bool operator==(Cell *cell) {
        return this->row == cell->getRow() && this->col == cell->getCol();
    }


};


#endif //EX4_CELL_H
