//
// Created by Devin Plauche on 1/28/20.
//
#include "Datalogprogram.h"
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
string Datalog::toString() {
    stringstream outputString; // consider stringstream
    if(!schemesVector.empty() && !queriesVector.empty()) {

            outputString << "Schemes(" << schemesVector.size();
            outputString << "):\n";
            size_t size = schemesVector.size();
            for (size_t i = 0; i < size; i++) {
                outputString << "  " << schemesVector.at(i).toString();//check
                outputString << "\n";
            }



            vector<string> domainVector;
        if (!factsVector.empty()) {
            outputString << "Facts(" << factsVector.size();
            outputString << "):\n";
            size_t size = factsVector.size();
            for (size_t i = 0; i < size; i++) {
                outputString << "  " << factsVector.at(i).toString() << ".";
                outputString << "\n";
                int length = factsVector.at(i).paramVector.size();
                for (int j = 0; j < length; j++) {
                    domainVector.push_back(factsVector.at(i).paramVector.at(j).paramValue);

                }

            }

        }
        else {
            outputString << "Facts(0):" << endl;
        }
        if (!rulesVector.empty()) {
            outputString << "Rules(" << rulesVector.size();
            outputString << "):\n";
            size_t size = rulesVector.size();
            for (size_t i = 0; i < size; i++) {
                outputString << "  " << rulesVector.at(i).toString();
                outputString << "\n";
            }

        }
        else {
            outputString << "Rules(0):" << endl;
        }
        outputString << "Queries(" << queriesVector.size();
        outputString << "):\n";
        size_t qsize = queriesVector.size();
        for (size_t i = 0; i < qsize; i++) {
            outputString << "  " << queriesVector.at(i).toString() << "?";
            outputString << "\n";
        }

        sort(domainVector.begin(), domainVector.end());
        domainVector.erase(unique(domainVector.begin(), domainVector.end()), domainVector.end());
        outputString << "Domain(" << domainVector.size() << "):" << endl;
        for (size_t i = 0; i < domainVector.size(); i++) {
            outputString << "  " << domainVector.at(i) << endl;
        }
    }
    else {

        throw "missing required sections";
    }
   return outputString.str();
}
