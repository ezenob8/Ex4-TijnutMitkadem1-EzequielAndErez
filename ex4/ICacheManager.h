//
// Created by erez on 12/01/2020.z
//

#ifndef EX4_ICACHEMANAGER_H
#define EX4_ICACHEMANAGER_H

//cache manager
template<class P, class S>
class ICacheManager {
public:
    virtual S get(P key) = 0;//get from cache
    virtual void insert(P key, S obj) = 0;//insert to cache
    virtual bool isSolutionExists(P key)=0;//check if solution exists
};


#endif //EX4_ICACHEMANAGER_H
