//
// Created by Devin Plauche on 4/11/20.
//

#include "Graph.h"
#include<iostream>
#include <sstream>
void Graph::depthFirstSearch(vector<pair<Node,Node>> &localGraph, Node &inputNode) {
    //cout << "New Iteration" << endl;
    size_t lSize = localGraph.size();

    inputNode.visited = true; //initially visit node
    sccNodes.push_back(inputNode.nodeId);
    nodeMap[inputNode.nodeId].visited = true; // copy condition to map

        for (size_t i = 0; i < lSize; i++) {
            if (inputNode.nodeId == localGraph[i].first.nodeId) {

                if (!localGraph[i].second.visited && !nodeMap[localGraph[i].second.nodeId].visited) { // visit child
                    //inputNode.visited = true;
                    //cout << "Node Id: " << nodeMap[localGraph[i].second.nodeId].nodeId << endl;

                    localGraph[i].second.visited = true;
                    nodeMap[localGraph[i].second.nodeId].visited = true;
                    depthFirstSearch(localGraph, localGraph[i].second); // recursively create trees

                }

            }

        }
        inputNode.postOrderNumber = counter;
        nodeMap[inputNode.nodeId].postOrderNumber = counter;

        //cout << "New Iteration" << endl;
        //sccNodes.push_back(inputNode.nodeId);
        //cout << "PostorderNum: " <<inputNode.postOrderNumber << endl;
        //nodeMap[inputNode.nodeId].postOrderNumber = counter;

        nodeMap[inputNode.nodeId].visited = true;
        counter++;

}

string Graph::toString() {
    stringstream os;
    size_t eSize = edgeVector.size();
    for(size_t i = 0; i < eSize; i++) {
        for(size_t j = 0; j < eSize; j++) {
            if(edgeVector[i].first.nodeId == edgeVector[j].first.nodeId) {
                os << "R" << edgeVector[i].first.nodeId << ":";
                for(size_t k = 0; k < eSize; k++) {
                   if(edgeVector[i].first.nodeId == edgeVector[k].first.nodeId) {
                       os << "R" << edgeVector[k].second.nodeId << ",";
                   }
                }
                cout << endl;
            }

        }

    }
    return os.str();
}
/*visitNode(localGraph[i].second); // visits linked node
        localGraph[i].second.postOrderNumber = counter;*/