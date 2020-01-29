//
// Created by erez on 18/01/2020.
//

#ifndef EX4_ISEARCHER_H
#define EX4_ISEARCHER_H

#include <string>
#include "ISearchable.h"

using namespace std;
//interface for classes that perform search algorithms
template<class S, class T>
class ISearcher {
public:
    virtual S search(ISearchable<T> *searchable) = 0;
};

#endif //EX4_ISEARCHER_H
