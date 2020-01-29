//
// Created by erez on 18/01/2020.
//

#ifndef EX4_OA_H
#define EX4_OA_H

#include "ISolver.h"
#include "ISearcher.h"
#include "Matrix.h"
#include <cstring>

class OA : public ISolver<string, string> {
private:
    ISearcher<string, Cell *> *searcher;
public:
    string solve(string problem) override {
        //creating the matrix
        char *cstr = new char[problem.length() + 1];
        strcpy(cstr, problem.c_str());
        char *token = strtok(cstr, "\r\n");
        int n = 0;
        for (int i = 0; i < strlen(token); ++i) {
            if (token[i] == ',') {
                n++;
            }
        }
        int size = n+1;
        ISearchable<Cell *> *matrix = new Matrix(size, problem);
        return searcher->search(matrix);//activating the algorithm to solve the problem
    }

    OA() = default;

    //constructor
    explicit OA(ISearcher<string, Cell *> *searcher1) {
        this->searcher = searcher1;
    }


};


#endif //EX4_OA_H
