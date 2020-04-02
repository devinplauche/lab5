//
// Created by Devin Plauche on 3/15/20.
//

#include "Database.h"

Relation Database::lookUpRelation(string searchName) {
    Relation emptyObj("failure to look up");
    size_t drSize = databaseRelations.size();
    for(size_t i = 0; i < drSize; i++) {
        if(searchName == databaseRelations.at(i).relationName)
        {
            return databaseRelations.at(i);
        }
    }
    return emptyObj;  //error

}

Database::Database() {

}
