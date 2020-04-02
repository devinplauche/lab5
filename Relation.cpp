//
// Created by Devin Plauche on 3/15/20.
//

#include "Relation.h"
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;
Relation Relation::naturalJoin(Relation inputRel) {
    Relation localObj;
    bool joinable;
    vector<pair<size_t,size_t >> samePos;
    vector<string> s1 = relationScheme.attributes;
    vector<string> s2 = inputRel.relationScheme.attributes;
    for(size_t i = 0; i < s1.size(); i++) {
        for(size_t j = 0; j < s2.size(); j++) {
            if(s1.at(i) == s2.at(j)) {
                samePos.push_back(pair<size_t,size_t>(i,j));
            }

        }
    }

    if(tupleSet.empty()) {
        for (set<Tuple>::iterator jt=inputRel.tupleSet.begin(); jt!=inputRel.tupleSet.end(); ++jt) { // check iterations excessive t1
            Tuple t2 = (*jt);
            localObj.tupleSet.insert(t2);
            localObj.relationScheme = inputRel.relationScheme;
        }
    }
    else {
       localObj.relationName = (inputRel.relationName);
    }

    for (set<Tuple>::iterator it=tupleSet.begin(); it!=tupleSet.end(); ++it) {
        for (set<Tuple>::iterator jt=inputRel.tupleSet.begin(); jt!=inputRel.tupleSet.end(); ++jt) { // check iterations excessive t1
            Tuple t1  = (*it);
            Tuple t2 = (*jt);

            joinable = isJoinable(t1, t2, samePos);

            if(joinable) { // FIXME

                localObj.relationScheme = combineSchemes(relationScheme, inputRel.relationScheme,  samePos);
                localObj.relationName = (inputRel.relationName + relationName); //?

                localObj.tupleSet.insert(combineTuples(t1,t2, samePos ));
            }

        }
    }

    return localObj;
}
//inRel is relation with proper Tuples from join
Relation Relation::Unite(Relation inRel) {
    Relation relationObj;
    relationObj.relationScheme = relationScheme;
    relationObj.relationName = relationName;
    relationObj.tupleSet = tupleSet; // copying (this) Relation
    addedTuple = false;


    for (set<Tuple>::iterator it=inRel.tupleSet.begin(); it!=inRel.tupleSet.end(); ++it) {
        relationObj.addTuple((*it));
    }

    return relationObj;
}

void Relation::addTuple(Tuple newTuple1) {
    if(!tupleSet.count(newTuple1)) { // if already in tuple
        addedTuple = true;
        tupleSet.insert(newTuple1);
        cout << tupleToString(newTuple1); // affects bool


    }

    //tupleSet.insert(newTuple1);



}

string Relation::tupleToString(Tuple tupleInSet) {
    stringstream os1;
    size_t size = tupleInSet.size();

    addedTuple = true;
    if (relationScheme.attributes.size() == size) {

        for (size_t i = 0; i < relationScheme.attributes.size(); i++) {
            if (i == 0) {
                os1 << "  ";
            }
            os1 << relationScheme.attributes.at(i) << "=" << tupleInSet.at(i);
            if (i != (size - 1)) {
                os1 << ", ";
            }

        }

    } else {
        cout << "---------------------hit";
        addedTuple = false;
       // tupleSet.erase(tupleInSet); // Checkme
        //os1 << "Inconsistent sizes relationScheme:" << relationScheme.attributes.size() << " tupleInSet" << tupleInSet.size();
    }
    if (addedTuple) {
        os1 << '\n';
    }




    return os1.str();
}
string Relation::toString() {

    stringstream os;


    for (set<Tuple>::iterator it=tupleSet.begin(); it!=tupleSet.end(); ++it) {
        string localVar;
        if(!(*it).empty()) {
            localVar = tupleToString(*it);
        }
        os << localVar ;

    }


    return os.str();
}
Relation Relation::selectConstant(int col, string value) {

        Relation relationObj;
         relationObj.relationScheme = relationScheme;
        relationObj. relationName = relationName;

        for (set<Tuple>::iterator it = tupleSet.begin(); it != tupleSet.end(); ++it) {
            Tuple localTuple = (*it);
            if (localTuple.at(col) == value) {

                relationObj.tupleSet.insert(localTuple);
            }

        }


    return relationObj;


}
Relation Relation::selectVariable(int col1, int col2) {
     Relation relationObj;
     relationObj.relationScheme = relationScheme;
     relationObj.relationName = relationName;


    for (set<Tuple>::iterator it=tupleSet.begin(); it!=tupleSet.end(); ++it) {
        Tuple localTuple = (*it);
        if(localTuple.at(col1) == localTuple.at(col2)) {
            relationObj.tupleSet.insert(localTuple);
        }
    }

    return relationObj;
}

Relation Relation::projectCol(vector<int> keepCols) { // change to vector
    Relation relationObj;
    relationObj.relationName = relationName;
    relationObj.relationScheme = relationScheme;

    for (set<Tuple>::iterator it=tupleSet.begin(); it!=tupleSet.end(); ++it) {
        Tuple localTuple = (*it);
        Tuple keepStrings;

        for(size_t i = 0; i < keepCols.size(); i++) {
            keepStrings.push_back(localTuple.at(keepCols.at(i))); // check
            //cout << localTuple.at(keepCols.at(i));
        }

        localTuple = keepStrings;
        relationObj.tupleSet.insert(localTuple);
    }

    return relationObj;
}

Relation Relation::renameScheme(vector<string> inputScheme) {
    Relation relationObj;
    relationObj.relationName = relationName;
    relationObj.relationScheme.attributes = inputScheme;
    relationObj.tupleSet = tupleSet;
    return relationObj;

}
bool Relation::isJoinable(Tuple t1, Tuple t2, vector<pair<size_t,size_t>> pos) {


    for (size_t k = 0; k < pos.size(); k++) {
        if(t1.at(pos.at(k).first) != t2.at(pos.at(k).second)) {

            return false;

        }

    }


    return true;
}
Scheme Relation::combineSchemes(Scheme localScheme, Scheme inScheme, vector<pair<size_t,size_t >> samePos1) {
    size_t counter = 0;

        for (size_t i = 0; i < inScheme.attributes.size(); i++) {
            if(!samePos1.empty()) { // joins pairs
                if ((samePos1.at(counter).second != i)) {
                    localScheme.attributes.push_back(inScheme.attributes.at(i));
                } else if (samePos1.at(counter).second == i) {
                    if (counter < samePos1.size() - 1) {
                        counter++;
                    }
                }
            }
            else { // just adds all values
                localScheme.attributes.push_back(inScheme.attributes.at(i));
            }
        }


    return localScheme;
}
Tuple Relation::combineTuples(Tuple inTuple, Tuple combTuple, vector<pair<size_t,size_t >> samePos2) {
    size_t counter = 0;
    for(size_t i = 0; i < combTuple.size(); i++) {
        if(!samePos2.empty()) { // joins pairs
            if ((samePos2.at(counter).second != i)) {
                inTuple.push_back(combTuple.at(i));
            } else if (samePos2.at(counter).second == i) {

                if (counter < samePos2.size() - 1) {
                    counter++;
                }
            }
        }
        else { // just adds all values
            inTuple.push_back(combTuple.at(i));
        }
    }
    return inTuple;
}
















Relation Relation::selectMultVariable(vector<int> colNums ,vector<string> dupParams) {
    Relation relationObj;
    relationObj.relationName = relationName;
    relationObj.relationScheme = relationScheme;

    for (set<Tuple>::iterator it=tupleSet.begin(); it!=tupleSet.end(); ++it) {
        Tuple localTuple = (*it);
        for(size_t i = 0; i < colNums.size(); i++) {
            for(size_t j = 0; j < colNums.size(); j++) {

                if (localTuple.at(colNums.at(i)) == localTuple.at(colNums.at(j)) && (i != j) ) { // && duplicate param == query param

                    relationObj.tupleSet.insert(localTuple); //set won't add duplicate tuples

                }

            }
        }

    }
    return relationObj;
}
/* Tuple newTuple;
    Scheme newScheme;
    string newName;
    newTuple = t1; //copy t1 to newTuple
    newScheme = relationScheme; // copy s1 to newScheme
    newName = relationName;
    for(size_t m = 0; m < s2Size; m++) {
        if(relationScheme.attributes.at(m) != inputRel.relationScheme.attributes.at(j)) { // check logic
            newScheme.attributes.push_back(relationScheme.attributes.at(m));
            newName.push_back(relationScheme.attributes.at(m).at(0)); //FIXME
            newTuple.push_back(t2.at(m));
        }
    }

    relationObj.relationScheme = newScheme; // add to return relation
    relationObj.relationName = newName; // FIXME
    relationObj.tupleSet.insert(newTuple);*/
//old code for joinable
/* for (size_t k = 0; k < t1.size(); k++) {
                for (size_t l = 0; l < t2.size(); l++) {

                    if (t1.at(k) != t2.at(l)) { // if vals don't match and cols do

                        joinable = false;


                    } else if (t1.at(k) == t2.at(l)) {
                        //cout << "Tuples:" << t1.at(k) << t2.at(l) << endl;
                        //cout << "Schemes:" << s1.attributes.at(i) << s2.attributes.at(j) << endl;
                        joinable = true;
                        return joinable;
                    }
                }*/
/*Relation Relation::renameScheme(vector<int> keepCols, vector<string> val) {
    Relation relationObj;
    relationObj.relationName = relationName;
    relationObj.relationScheme = relationScheme;
    relationObj.tupleSet = tupleSet;
    for(size_t i = 0; i < keepCols.size(); i++) {
        relationObj.relationScheme.attributes.at(keepCols.at(i)) = val.at(i);
    }

    return relationObj;
}*/