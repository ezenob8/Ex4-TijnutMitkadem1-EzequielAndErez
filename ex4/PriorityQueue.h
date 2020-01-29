//
// Created by erez on 27/01/2020.
//

#ifndef EX4_PRIORITYQUEUE_H
#define EX4_PRIORITYQUEUE_H

#include <queue>
#include "State.h"

using namespace std;
//expanding the priority queue STL and adding more functionality
template<class T,class Container = vector<T>, class Compare = greater<typename Container::value_type>
>
class PriorityQueue : public std::priority_queue<T, Container, Compare> {
public:
    typedef typename
    std::priority_queue<
            T,
            Container,
            Compare>::container_type::const_iterator const_iterator;

    //return true if a val is in the priority queue
    bool find(const T &val) {
        auto first = this->c.cbegin();
        auto last = this->c.cend();
        while (first != last) {
            if (*first == val) {
                return true;
            }
            ++first;
        }
        return false;
    }

    //remove from priority queue
    void remove(const T &value) {
        auto it = std::find(this->c.begin(), this->c.end(), value);
        if (it != this->c.end()) {
            this->c.erase(it);
            std::make_heap(this->c.begin(), this->c.end(), this->comp);
        }
    }
};


#endif //EX4_PRIORITYQUEUE_H
