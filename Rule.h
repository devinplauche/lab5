//
// Created by Devin Plauche on 1/28/20.
//

#ifndef RULE_H
#define RULE_H
#include "Predicate.h"
#include <vector>
using namespace std;
class Rule {
public:
    Rule() {};
    string toString();
    vector<Predicate> leftPredicate; // only as vector for copying purposes
    vector<Predicate> rightPredicates;
};

#endif //LAB2_RULE_H
