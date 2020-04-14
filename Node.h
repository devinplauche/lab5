//
// Created by Devin Plauche on 4/11/20.
//

#ifndef LAB4_NODE_H
#define LAB4_NODE_H

#include <set>
using namespace std;

class Node {
public:
    Node() {
        postOrderNumber = 0;
        visited = false;
        printed = false;
        dependsOnItself = false;
    }
    bool visited;
    bool printed;
    size_t postOrderNumber;
    size_t nodeId;
    set<size_t> edgeSet;
    bool dependsOnItself;

};


#endif //LAB4_NODE_H
