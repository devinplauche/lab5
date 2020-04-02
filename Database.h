//
// Created by Devin Plauche on 3/15/20.
//

#ifndef LAB3_DATABASE_H
#define LAB3_DATABASE_H
#include <map>
#include "Relation.h"

class Database : public map<string, Relation>{
public:
    Database();
    vector<Relation> databaseRelations;
    Relation lookUpRelation(string);
};


#endif //LAB3_DATABASE_H
