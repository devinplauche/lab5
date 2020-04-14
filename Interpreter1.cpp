//
// Created by Devin Plauche on 3/16/20.
//

#include "Interpreter1.h"
#include "Tuple.h"
#include "Relation.h"
#include <iostream>
#include <map>
#include "Node.h"
#include "Graph.h"
#include <sstream>
#include <algorithm>

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
void Interpreter::buildDependencyGraph() {
    //Graph newGraph;
    set<string> nodeNames; // used to check for duplicates
    size_t rvSize = rootData.rulesVector.size();
    for (size_t i = 0; i < rvSize; i++) {
        string headPredicate = rootData.rulesVector.at(i).leftPredicate.at(
                0).predicateName; // used for checking for duplicates
        Node newNode;
        newNode.nodeId = i;
        newGraph.nodeMap[i] = newNode;
        /*if(!nodeNames.count(headPredicate)) { // if not already in set
            newGraph.nodeMap[i] = newNode;
        }
        nodeNames.insert(headPredicate); // used for duplicate check*/
    }
    // make edges in for loop
    // rename variables for convenience
    // size_t ngSize = newGraph.nodeMap.size();
    cout << "Dependency Graph" << endl;
    for (size_t i = 0; i < rvSize; i++) {
        stringstream os;
        vector<Predicate> bodyPredicates = rootData.rulesVector.at(i).rightPredicates;
        size_t bSize = bodyPredicates.size();
        Node newNode;
        string removeComma;
        vector<size_t> dependecyEdges;
        newNode.nodeId = i;
        cout << "R" << i << ":";
        for (size_t j = 0; j < bSize; j++) {

            for (size_t k = 0; k < rvSize; k++) {
                string innerHeadPredicate = rootData.rulesVector.at(k).leftPredicate.at(0).predicateName;
                Node innerNode;
                innerNode.nodeId = k;
                if (bodyPredicates.at(j).predicateName == innerHeadPredicate) {
                    //cout << "Node" << newGraph.nodeMap[i].nodeId << endl;
                    //cout <<"Inner Node" <<  newGraph.nodeMap[k].nodeId << endl;

                    if(!newGraph.nodeMap[i].edgeSet.count(k)) {
                        dependecyEdges.push_back(k);
                    }
                    newGraph.nodeMap[i].edgeSet.insert(k);
                    //newGraph.nodeMap[k].edgeSet.insert(i);//reverseEdge
                    newGraph.edgeVector.emplace_back(pair<Node, Node>(newGraph.nodeMap[i], newGraph.nodeMap[k])); //CHECK
                    newGraph.reverseEdgeGraph.emplace_back(pair<Node, Node>(newGraph.nodeMap[k], newGraph.nodeMap[i]));//CHECK emplace instead of push


                }
            }

        }
        sort(dependecyEdges.begin(), dependecyEdges.end());
        for(size_t l = 0; l < dependecyEdges.size(); l++) {
            os << "R" << dependecyEdges[l] << ",";
        }
        removeComma = os.str();
        removeComma.pop_back();
        cout << removeComma;
        cout << endl;
        os.clear();
}
    cout << endl;

    /*size_t rdSize = newGraph.reverseEdgeGraph.size();
    for(size_t i = 0; i < rdSize; i++) {
        cout << "First" << newGraph.reverseEdgeGraph[i].first.nodeId << endl;
        cout << "Second" << newGraph.reverseEdgeGraph[i].second.nodeId << endl;
    }*/
    for (size_t i = 0; i < newGraph.nodeMap.size(); i++) {

        if (!newGraph.nodeMap[i].visited) {

            newGraph.depthFirstSearch(newGraph.reverseEdgeGraph, newGraph.nodeMap[i]);
        }

    }

    vector<pair<size_t, size_t>> postOrderNumbers;
    for (size_t i = 0; i < newGraph.nodeMap.size(); i++) {

        postOrderNumbers.push_back(pair<size_t, size_t>(newGraph.nodeMap[i].postOrderNumber, i));
        newGraph.nodeMap[i].visited = false; // resets values
    }
    sort(postOrderNumbers.begin(), postOrderNumbers.end());
    newGraph.sccNodes.clear();
    newGraph.counter = 1;
    size_t index = 0;
    bool pushLater = false;
    for (size_t i = 0 ; i < newGraph.nodeMap.size(); i++) {
        if(newGraph.nodeMap[i].edgeSet.count(i)) {
            newGraph.nodeMap[i].dependsOnItself = true;
            //cout << "depends-----" << i << endl;
        }
    }

    for (size_t i = newGraph.nodeMap.size() - 1; i >= 0; --i) { //FIXME type warning before submission
        if(newGraph.nodeMap.size() == 0){
            break;
        }
        index = postOrderNumbers[i].second;

        if (newGraph.nodeMap[index].visited) {
            //newGraph.sccNodes.push_back(index);

            pushLater = false;
        } else {
            pushLater = true;
        }
        newGraph.depthFirstSearch(newGraph.edgeVector, newGraph.nodeMap[index]);

        if (pushLater) {

            nodesInSCC.push_back(newGraph.sccNodes);
        }
        newGraph.sccNodes.clear();
        if(i == 0){
            break;
        }
    }
    /*for (size_t i = 0; i < nodesInSCC.size(); i++) {
        for (size_t j = 0; j < nodesInSCC[i].size(); j++) {
            cout << nodesInSCC[i][j];
        }
        cout << endl;
    }*/




}

void Interpreter::evaluateRules() {
    cout << "Rule Evaluation" << endl;
    size_t numPasses = 0;
    bool newTuple = true;
    bool trueOnce = false;
    bool hitMultiple = false;
    //size_t rvSize = rootData.rulesVector.size();

    for (size_t i = 0; i < nodesInSCC.size(); i++) {
        newTuple =true;
        for(size_t j = 0; j < nodesInSCC[i].size(); j++) {

            Relation relationObj;
            //relationObj = evaluateRule(rootData.rulesVector.at(i));


            if(nodesInSCC[i].size() != 1 || newGraph.nodeMap[nodesInSCC[i][j]].dependsOnItself ){ //fixed point algorithm
                //cout << "hit fixed" << endl;
                if (newTuple) {
                cout << "SCC: ";
                for (size_t l = 0; l < nodesInSCC[i].size(); l++) {
                    cout << "R" << nodesInSCC[i][l];
                    if (l != nodesInSCC[i].size() - 1) {
                        cout << ",";
                    }
                }
                cout << endl;
                }

                while(newTuple) {

                    trueOnce = false;
                    hitMultiple = true;
                    for(size_t k = 0; k < nodesInSCC[i].size(); k++) { // FIXME (i<size)
                        cout << rootData.rulesVector.at(nodesInSCC[i][k]).toString() << endl;
                        //Relation relationObj;
                        relationObj = evaluateRule(rootData.rulesVector.at(nodesInSCC[i][k]));

                        newTuple = relationObj.addedTuple;


                        if(newTuple) {
                            trueOnce = true; //keeps true if one is true
                        }

                    }
                    newTuple = trueOnce; // puts value back

                    numPasses++;
                }
                if(hitMultiple) {
                    cout << numPasses << " passes: ";
                    for (size_t l = 0; l < nodesInSCC[i].size(); l++) {
                        cout << "R" << nodesInSCC[i][l];
                        if (l != nodesInSCC[i].size() - 1) {
                            cout << ",";
                        }
                    }
                    cout << endl;
                }
                hitMultiple = false;


            }
            else  { //FIXME check to see if it depends on itself!
                cout << "SCC: R" <<  nodesInSCC[i][j] << endl;

                cout << rootData.rulesVector.at(nodesInSCC[i][j]).toString() << endl; // the access works because of howe we assigned Ids
                relationObj = evaluateRule(rootData.rulesVector.at(nodesInSCC[i][j]));
                newTuple = relationObj.addedTuple;
                numPasses++;
                cout <<  numPasses << " passes: R" << nodesInSCC[i][j] << endl;
            }


        }
        numPasses = 0;
    }


cout << endl;


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

        Predicate localPredicate = inputRule.rightPredicates.at(i);
        Relation orderObj = evaluateQuery(localPredicate);

        relationObj = relationObj.naturalJoin(orderObj); // joins each right predicate

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
