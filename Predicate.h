//
// Created by Devin Plauche on 1/28/20.
//

#ifndef PREDICATE_H
#define PREDICATE_H
#include <string>
#include <vector>
#include "Param.h"
using namespace std;
class Predicate {
public:

    Predicate(string nameIn) {
        predicateName=nameIn;
    };
    string predicateName;
    vector<Param> paramVector;
    string toString();
    void addParam(string paramIn);
};

#endif //LAB2_PREDICATE_H
