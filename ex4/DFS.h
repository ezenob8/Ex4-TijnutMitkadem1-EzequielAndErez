//
// Created by erez on 20/01/2020.
//

#ifndef EX4_DFS_H
#define EX4_DFS_H

#include "ISearcher.h"
#include <stack>
#include <unordered_set>

using namespace std;

#include "ISearchable.h"
#include "ISearcher.h"
#include <deque>
#include "cmath"
#include "list"

using namespace std;

template<class S, class T>
class DFS : public ISearcher<S, T> {
private:
    list<State<T> *> *visitedList = new list<State<T> *>();
    stack<State<T> *> *stateStack = new stack<State<T> *>();
public:
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

    bool isInVisitedList(State<T> *state) {
        for (typename list<State<T> *>::iterator it = visitedList->begin(); it != visitedList->end(); ++it) {
            if (state->equals(*it)) {
                return true;
            }
        }
        return false;
    }

    string search(ISearchable<T> *searchable) {
        //getting the first vertex to initial from
        State<T> *startState = searchable->getInitialState();
        //we will run DFS by using a stack,path initial state and searchable (our matrix or graph)
        // Mark the current node as visited and enqueue it
        visitedList->push_back(startState);
        // add the source node to the openList list which is a stack data structure
        stateStack->push(startState);
        // create an iterator to iterate through the adjacency list
        typename list<State<T> *>::iterator i;
        // while the stack is not empty
        while (!stateStack->empty()) {
            // Pop a vertex from stack;
            State<T> *u = stateStack->top();
            stateStack->pop();
            // if the popped state was not visited marked it
            if (!isInVisitedList(u)) {
                //the came from state is the last state in the visited List
                State<T> *prevState = visitedList->front();
                visitedList->push_back(u);
                u->setParent(prevState);
                //set the new sum of cost
                int newCost = prevState->getTotalCost() + u->getCost();
                u->setTotalCost(newCost);
                //if we in the goal state
                if (searchable->isGoalState(u)) {
                    return getPath(u, searchable);
                    //if we want to return the total number if nodes that the algorithm passed
                    //return to_string(this->evaluatedNodes);
                }
            }
            // Get all adjacent vertices of the popped vertex u
            // If a adjacent has not been visited, then push it
            // to the stack.
            vector<State<T> *> *neighbours = searchable->getAllPossibleStates(u);
            for (typename vector<State<T> *>::iterator it = neighbours->begin(); it != neighbours->end(); ++it) {
                if (*it != NULL && !isInVisitedList(*it)) {
                    stateStack->push(*it);
                }
            }
        }
    }

};

#endif //EX4_DFS_H
