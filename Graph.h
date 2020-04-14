//
// Created by Devin Plauche on 4/11/20.
//

#ifndef LAB4_GRAPH_H
#define LAB4_GRAPH_H

#include<map>
#include<vector>
#include "Node.h"
using namespace std;
class Graph {
public:
    map<size_t, Node> nodeMap;
    vector<pair<Node ,Node>> edgeVector;
    vector<pair<Node, Node>> reverseEdgeGraph;
    void depthFirstSearch(vector<pair<Node,Node>> &inGraph, Node &startingNode);
    size_t counter = 1;
    vector<size_t> sccNodes;


    string toString();
};


#endif //LAB4_GRAPH_H
