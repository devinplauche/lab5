//
// Created by Devin Plauche on 3/15/20.
//

#ifndef RELATION_H
#define RELATION_H
#include "Tuple.h"
#include "Scheme.h"
#include <set>
#include <vector>
#include <string>
#include "Param.h"
using namespace std;

class Relation {
public:
        Relation() {

        }
        Relation(const string inputString)  { // check
             relationName = inputString;
        }

        void addTuple(Tuple newTuple1);
        string toString();
        string tupleToString(Tuple passByVal);

    Scheme relationScheme;
    string relationName;
    set<Tuple> tupleSet;

    Relation selectConstant(int col, string value);
    Relation selectVariable(int col1, int col2); // only for duplicates
    Relation selectMultVariable(vector<int> colNums, vector<string> dupParams);
    Relation projectCol(vector<int> keepCols);
    bool isJoinable(Tuple inTup1, Tuple inTup2, vector<pair<size_t,size_t>> pos1);
    Scheme combineSchemes(Scheme localScheme, Scheme inputScheme, vector<pair<size_t,size_t >> samePosa);
    Tuple combineTuples(Tuple inputTuple, Tuple combTuple, vector<pair<size_t,size_t >> samePosb);
    Relation renameScheme(vector<string> inputScheme);
    Relation naturalJoin(Relation inputRel);
    bool addedTuple;
    Relation Unite(Relation inRel);
};


#endif //LAB3_RELATION_H
