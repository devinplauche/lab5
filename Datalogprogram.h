//
// Created by Devin Plauche on 1/28/20.
//

#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H
#include <vector>
#include <string>
#include "Rule.h"
#include "Predicate.h"
class Datalog {
public:
    Datalog(){};
    vector<Rule> rulesVector;
    vector<Predicate> queriesVector;
    vector<Predicate> factsVector;
    vector<Predicate> schemesVector;
    string toString();
};

#endif //LAB2_DATALOGPROGRAM_H
