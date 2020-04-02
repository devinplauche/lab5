#ifndef INTERPRETER1_H
#define INTERPRETER1_H
#include "Datalogprogram.h"
#include "Relation.h"
#include "Tuple.h"
#include "Database.h"
#include<vector>

class Interpreter { ;

public:
    Interpreter(Datalog inputProgram){
        rootData = inputProgram;
        parseInput();


    }
    Relation evaluateQuery(Predicate Query); // input is query
    Relation evaluateRule(Rule inputRule);
    void evaluateAllQueries(); // come back to this FIXME
    void parseInput();
    void evaluateRules();
    Datalog rootData;
    size_t numSuccesful;



    Database databaseObj;
    vector<Relation> relationVector;
    vector<Tuple> tupleVector;
};


#endif //LAB3_INTERPRETER_H

