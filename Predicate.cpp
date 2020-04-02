//
// Created by Devin Plauche on 1/28/20.
//
#include "Predicate.h"
#include <sstream>
string Predicate::toString() {
    stringstream predicateString;
    predicateString << predicateName;
    predicateString <<'(';
    size_t listSize = paramVector.size();
    for(size_t i = 0; i < listSize; i++) {
        predicateString << paramVector.at(i).toString() << ",";
    }
    string outputString = predicateString.str();
    outputString.pop_back();

    outputString += ')';
    return outputString;
}
void Predicate::addParam(string paramIn) {
    Param newParam(paramIn);
    paramVector.push_back(newParam);
}
