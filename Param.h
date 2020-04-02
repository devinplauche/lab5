//
// Created by Devin Plauche on 1/28/20.
//

#ifndef PARAM_H
#define PARAM_H
#include <string>
using namespace std;
class Param {
public:
    Param(string valueIn) {
        paramValue = valueIn;
        isConstant = false;
    };
    string paramValue;
    bool isConstant;
    string toString();
};

#endif //LAB2_PARAM_H
