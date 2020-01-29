//
// Created by erez on 15/01/2020.
//

#ifndef EX4_FILECACHEMANAGER_H
#define EX4_FILECACHEMANAGER_H

#include <unordered_map>
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include "ICacheManager.h"

using namespace std;

template<class P, class S>
class FileCacheManager : public ICacheManager<P, S> {
private:
    hash<P> hasher;
public:

    FileCacheManager<P, S>() {

    }

    void insert(P key, S obj) override {
        string fileName = "sol_" + to_string(hasher(key)) + ".txt";
        ofstream file;
        file.open(fileName);
        if (!file) {
            const char *e = "file wont initial";
            throw e;
        }
        file << obj << endl;
        file.close();

    }

    S get(P key) override {
        string fileName = "sol_" + to_string(hasher(key)) + ".txt";
        ifstream file;
        file.open(fileName);
        //the key is in a file
        if (file.is_open()) {
            S obj;
            getline(file, obj);
            string sol = "";
           // strcpy(sol, obj);
            file.close();
            return obj;
        }
    }

    bool isSolutionExists(P key) {
        string fileName = "sol_" + to_string(hasher(key));
        ifstream file;
        file.open(fileName, ios::in);
        //the key is in a file
        return file.is_open();
    }

    ~FileCacheManager() {

    }

};


#endif //EX4_FILECACHEMANAGER_H
