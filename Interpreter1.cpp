//
// Created by Devin Plauche on 3/16/20.
//

#include "Interpreter1.h"
#include "Tuple.h"
#include "Relation.h"
#include <iostream>
#include <map>

void Interpreter::parseInput() {
    size_t scSize = rootData.schemesVector.size();
    size_t fSize = rootData.factsVector.size();

    for(size_t i = 0; i < fSize; i++) { // make a tuple for each fact
        size_t paramSize = rootData.factsVector.at(i).paramVector.size();
        Tuple tupleObj;
        tupleVector.push_back(tupleObj); // check mem allocation
        for(size_t j = 0; j < paramSize; j++) {
            tupleVector.at(i).push_back(rootData.factsVector.at(i).paramVector.at(j).paramValue); // check for size 0 of tupleVector
        }
    }

    for(size_t i = 0; i < scSize; i++) { // make a relation for each scheme
        string schemeName = rootData.schemesVector.at(i).predicateName;
        Relation relationObj(schemeName);
        relationVector.push_back(relationObj);

        size_t parSize = rootData.schemesVector.at(i).paramVector.size();
        for(size_t j = 0; j < parSize; j++) {

            relationVector.at(i).relationScheme.attributes.push_back(rootData.schemesVector.at(i).paramVector.at(j).paramValue); // check for correct acceses of vectors
        }
    }
    for(size_t i = 0; i < scSize; i++) { // place tuples in relations
        string schemeName = rootData.schemesVector.at(i).predicateName;

        for(size_t j = 0; j < fSize; j++) {
            string factName = rootData.factsVector.at(j).predicateName;
            if (schemeName == factName) {

                relationVector.at(i).tupleSet.insert(tupleVector.at(j)); // place tuples in relations
            }


        }
        databaseObj.databaseRelations.push_back(relationVector.at(i));

    }



}
/*
Relation Interpreter::evaluateQuery(Predicate Query) {
    size_t qSize = Query.paramVector.size();
    string searchString = Query.predicateName;
    Relation localRelation = databaseObj.lookUpRelation(searchString);
    vector<string> newScheme;
    map<string, int> locations;
    vector<int> indexes;
    for (size_t i = 0; i < qSize; i++){
        if(Query.paramVector.at(i).isConstant){
            localRelation = localRelation.selectConstant(i, Query.paramVector.at(i).paramValue);
        }
        else {

            if((locations.end()->second) == locations[Query.paramVector.at(i).paramValue]){
                locations[Query.paramVector.at(i).paramValue] = i;
                newScheme.push_back(Query.paramVector.at(i).paramValue);
                indexes.push_back(i);
            } else {
                localRelation = localRelation.selectVariable(i, locations[Query.paramVector.at(i).paramValue]);
            }
        }
    }

    localRelation= localRelation.projectCol(indexes);
    localRelation = localRelation.renameScheme(newScheme);

    if(localRelation.tupleSet.size() > 0) {
        numSuccesful = localRelation.tupleSet.size();
        successfulQuery = true;
    }
    else {
        successfulQuery = false;
    }

    return localRelation;
}*/

void Interpreter::evaluateRules() {
    cout << "Rule Evaluation" << endl;
    size_t numPasses = 0;
    bool newTuple = true;
    bool trueOnce = false;
    while(newTuple) {
        trueOnce = false;
        for(size_t i = 0; i < rootData.rulesVector.size(); i++) {
            cout << rootData.rulesVector.at(i).toString() << endl;

            newTuple = evaluateRule(rootData.rulesVector.at(i)).addedTuple;
           // cout << "Bool value:" << newTuple << endl;
            if(newTuple) {
                trueOnce = newTuple; //keeps true if one is true
            }

        }
        newTuple = trueOnce; //
        //cout << "numPasses:" << numPasses << endl;
        numPasses++;
    }

    cout << endl << "Schemes populated after " << numPasses << " passes through the Rules." << endl << endl;


}
Relation Interpreter::evaluateRule(Rule inputRule) {

    Relation relationObj;
    relationObj.relationName = inputRule.leftPredicate.at(0).predicateName;

    size_t lSize = relationObj.relationScheme.attributes.size();
    size_t rSize = inputRule.leftPredicate.at(0).paramVector.size();
    vector<string> lName = relationObj.relationScheme.attributes;

    vector<Param> rName = inputRule.leftPredicate.at(0).paramVector;
    vector<int> posOfLeftCols;
    size_t qSize = inputRule.rightPredicates.size();

    for(size_t i = 0; i < (qSize); i++) { //FIXME

        relationObj = relationObj.naturalJoin(evaluateQuery(inputRule.rightPredicates.at(i))); // joins each right predicate

       if( i == (inputRule.rightPredicates.size() - 1)) { // only call on last iteration
           lSize = relationObj.relationScheme.attributes.size();
           lName = relationObj.relationScheme.attributes;

        }




    }

    // project columns that appear in the head predicate
    for(size_t i = 0; i < inputRule.leftPredicate.at(0).paramVector.size(); i++) {
        for (size_t j = 0; j < lSize; j++) {
            for (size_t k = 0; k < rSize; k++) {

                if (lName.at(j) == rName.at(k).paramValue && lName.at(j) == inputRule.leftPredicate.at(0).paramVector.at(i).paramValue) {

                    posOfLeftCols.push_back(j);
                    //cout << lName.at(j);



                }
            }
        }
    }

    relationObj = relationObj.projectCol(posOfLeftCols);

    // rename and unite
    size_t drSize = databaseObj.databaseRelations.size();
    for(size_t j = 0; j < drSize; j++) {
        if(inputRule.leftPredicate.at(0).predicateName == databaseObj.databaseRelations.at(j).relationName) {
            relationObj = relationObj.renameScheme(databaseObj.databaseRelations.at(j).relationScheme.attributes);
            databaseObj.databaseRelations.at(j) = databaseObj.databaseRelations.at(j).Unite(relationObj); // Unite
            relationObj.addedTuple = databaseObj.databaseRelations.at(j).addedTuple;
        }
    }



    //cout <<  relationObj.toString();

    return relationObj;
}




Relation Interpreter::evaluateQuery(Predicate Query) {
    // should call selects on relation class
    size_t qSize = Query.paramVector.size();
    string searchString = Query.predicateName;

    Relation localRelation = databaseObj.lookUpRelation(searchString);

    Relation finalRelation;

    finalRelation.relationScheme = localRelation.relationScheme;
    finalRelation.relationName = localRelation.relationName;
    vector<int> keepCols;
    vector<string> valsRename;
    vector<string> duplicateValues;
    vector<int> positionOfDuplicate;
    vector<int> positionOfVar;
    set<int> checkDup;
    set<string> checkDupVal;
    int counter = 0;
    for (size_t i = 0; i < qSize; i++) { // select

        for (size_t j = 0; j < qSize; j++) {
            if(!Query.paramVector.at(i).isConstant) {
                positionOfVar.push_back(i);
            }
            if (Query.paramVector.at(i).paramValue == Query.paramVector.at(j).paramValue && (i != j) && !Query.paramVector.at(i).isConstant) {


                if (!checkDupVal.count(Query.paramVector.at(i).paramValue)) { // if not already in vector
                    checkDupVal.insert(Query.paramVector.at(i).paramValue);
                    duplicateValues.push_back(Query.paramVector.at(i).paramValue);
                    checkDup.insert(i);
                    positionOfDuplicate.push_back(i);
                }

            }


        }
    }

    for (size_t i = 0; i < qSize; i++) { // select



        if (Query.paramVector.at(i).isConstant) {
            localRelation = localRelation.selectConstant(i, Query.paramVector.at(i).paramValue);
            numSuccesful = localRelation.tupleSet.size();


        } else {

            for (size_t k = 0; k < duplicateValues.size(); k++) { // duplicates
                if(duplicateValues.at(k) == Query.paramVector.at(i).paramValue) {
                    localRelation = localRelation.selectVariable(i, k);
                }

                /*if (positionOfDuplicate.size() > 1 && i == (qSize - 1)) {

                    localRelation = localRelation.selectMultVariable(positionOfDuplicate, duplicateValues);
                }*/



            }



            if (positionOfDuplicate.size() > 0 && checkDup.count(i)) {
                keepCols.push_back(positionOfDuplicate.at(counter));
                valsRename.push_back(duplicateValues.at(counter));
                counter++;
            }
                /*else if (positionOfDuplicate.size() > 1 && (i == positionOfLastDuplicate)) { // more than 1 duplicate

                    for (size_t b = 0; b < duplicateValues.size(); b++) {

                        keepCols.push_back(positionOfDuplicate.at(b));
                        valsRename.push_back(duplicateValues.at(b));

                    }


                }*/
            else if(!checkDupVal.count(Query.paramVector.at(i).paramValue)){

                keepCols.push_back(i);
                valsRename.push_back(Query.paramVector.at(i).paramValue);


            }
        }
    }


    localRelation = localRelation.renameScheme(valsRename);
    localRelation = localRelation.projectCol(keepCols);




    if(localRelation.tupleSet.size() > 0) {
        numSuccesful = localRelation.tupleSet.size();


    }



    return localRelation;

}

void Interpreter::evaluateAllQueries() {
    cout << "Query Evaluation" << endl;
    for(size_t i = 0; i < rootData.queriesVector.size(); i++) {

        cout << rootData.queriesVector.at(i).toString() <<"? ";
        Relation toPrint =  evaluateQuery(rootData.queriesVector.at(i));
        if (toPrint.tupleSet.size() == 0) {
            cout << "No\n";
        }

        else {
            cout << "Yes(" << numSuccesful << ")\n";
            cout << toPrint.toString();
        }
    }
}
