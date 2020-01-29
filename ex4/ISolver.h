//
// Created by erez on 12/01/2020.
//

#ifndef EX4_ISOLVER_H
#define EX4_ISOLVER_H

//interface of classes the solve problems
template <typename S, typename P>
class ISolver {
public:
    virtual S solve(P problem) = 0;
};


#endif //EX4_ISOLVER_H
