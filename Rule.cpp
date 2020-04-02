//
// Created by Devin Plauche on 1/28/20.
//

#include "Rule.h"
#include <sstream>
string Rule::toString() {

    stringstream ostream;
    ostream << leftPredicate.at(0).toString() << " :- ";
    for(size_t i = 0; i < rightPredicates.size(); i++) {
        ostream << rightPredicates.at(i).toString() << ",";
    }
    string out = ostream.str();
    out.pop_back();
    out += ".";
    return out;
}