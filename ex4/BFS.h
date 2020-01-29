//
// Created by erez on 19/01/2020.
//

#ifndef EX4_BFS_H
#define EX4_BFS_H

#include "ISearcher.h"
#include "Cell.h"
#include <queue>
#include <vector>
#include <algorithm>
#include <stack>
#include <iostream>

using namespace std;

template<class S, class T>
class BFS : public ISearcher<S, T> {
    State<Cell *> *initial;
    vector<State<Cell *>> visited; //if a state is in visited vector, this state was previously visited
    queue<State<Cell *>> Q;
    double cost;

    void print_state(State<Cell *> *s) {
        cout << "State pos=(" << s->getState()->getRow() << ", " << s->getState()->getCol() << ") - Cost: "
             << s->getCost() << endl;
    }

public:
    BFS() { cost = 0; }
    string backTrace(State<T> *u, ISearchable<T> *searchable) {
        string str = "";
        while (!u->equals(searchable->getInitialState())) {
            auto *neighbours = searchable->getAllPossibleStates(u);
            State<T> *father = u->getCameFrom();
            if (father->equals(neighbours->at(0))) { //right
                cost += father->getCost();
                str += "Right (" + to_string(cost) + ")";
            } else if (father->equals(neighbours->at(1))) { //left
                cost += father->getCost();
                str += "Left (" + to_string(cost) + ")";
            } else if (father->equals(neighbours->at(2))) { //up
                cost += father->getCost();
                str += "Up (" + to_string(cost) + ")";
            } else if (father->equals(neighbours->at(3))) { //down
                cost += father->getCost();
                str += "Down (" + to_string(cost) + ")";
            } else {
                return "NULL";
            }
            u = u->getCameFrom();
        }
        return str;
    }
    
    string search(ISearchable<T> *searchable) override {
        initial = searchable->getInitialState();
        string solution = "";
        print_state(initial);
        visited.push_back(*initial); //store initial in visited
        Q.push(*initial); //put initial into the queue

        State<Cell *> *front_state;

        do {
            //copy of queue front
            front_state = &(Q.front());
            cout << "Front_state" << endl;
            print_state(front_state);
            //remove state from queue
            Q.pop();

            //check if this state is the goal state
            if (searchable->isGoalState(front_state)) {
                solution = reverseWay(searchable, front_state, searchable->getInitialState());
            } else {
                auto *adjacents = searchable->getAllPossibleStates(front_state);
                cout << "Adjacents states: " << endl;
                for (auto* adj : *adjacents) {
                    print_state(adj);
                    //this state is in visited vector?
                    /*     vector <State<Cell *>>::iterator it_vis = visited.begin();
                 while (it_vis != visited.end()) {
                        if (*it_vis == adj) {         //aca probar usar equals en lugar de ==
                               visited.push_back(adj);    //mark state as visited putting it into vector
                               Q.push(adj);               //add state to the queue to futher analysis
                    }
                    it_vis++;
                         } //while
      */
                } //for
            } //else
        } while (!Q.empty());

        solution += "There is no solution!";
        return solution;
    }

    string reverseWay(ISearchable<T> *searchable, State<Cell *> *goalState, State<Cell *> *initialState) {
        State<Cell *> *iter = goalState;
        if (iter->equals(initialState)) {
            return "Nothing, we are in the initialState state";
        }

        State<Cell *> *came = goalState->getCameFrom();
        string str;
        stack<string> my_stack;
        while (iter != initialState) {
            auto *neighbours = searchable->getAllPossibleStates(iter);
            if (came != NULL) {
                str = getStrByNeighbour(neighbours, came, iter);
                if (strcmp(str.c_str(), "NULL") == 0) {
                    return "There is no way";
                } else {
                    my_stack.push(str);
                }
                iter = came;
                came = iter->getCameFrom();
            }
        }
        return printWay(my_stack);
    }

    string getStrByNeighbour(vector<State<Cell *> *> *neighbours, State<Cell *> *came, State<Cell *> *iter) {
        if (came->equals(neighbours->at(0))) { //right
            cost += iter->getCost();
            return "Right (" + to_string(cost) + ")";
        } else if (came->equals(neighbours->at(1))) { //left
            cost += iter->getCost();
            return "Left (" + to_string(cost) + ")";
        } else if (came->equals(neighbours->at(2))) { //up
            cost += iter->getCost();
            return "Up (" + to_string(cost) + ")";
        } else if (came->equals(neighbours->at(3))) { //down
            cost += iter->getCost();
            return "Down (" + to_string(cost) + ")";
        } else {
            return "NULL";
        }
    }

    string printWay(stack<string> my_stack) {
        string strAll;
        while (!my_stack.empty()) {
            strAll += my_stack.top() + " ,";
            my_stack.pop();
        }
        return strAll.substr(0, strlen(strAll.c_str()) - 3);
    }
};

#endif //EX4_BFS_H
