//
// Created by Devin Plauche on 4/11/20.
//

#ifndef LAB4_NODE_H
#define LAB4_NODE_H

#include <set>
using namespace std;

class Node {
public:
    int nodeId;
    set<int> dependencies;
};


#endif //LAB4_NODE_H
