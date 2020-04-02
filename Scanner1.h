//
// Created by Devin Plauche on 1/18/20.
//

#ifndef SCANNER1_H
#define SCANNER1_H
#include <string>
#include <fstream>
#include "Token1.h"
/*enum TokenType {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY,
    ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED
};*/

class Scanner {
public:
    Scanner(string inputName)
    {
        fileName = inputName;
        c = 'a';
        ifs.open(inputName);
        totalTokens = 0;
        lineNum = 1;
        stringLineNum = 0;
    }
    ifstream ifs;
    string fileName;
    int c;
    void closeIfs();
    int getChar();
    int getLNum();
    int getTotalTokens();
    string getTString();
    int getStringLineNum();
    int stringLineNum;
    int lineNum;
    int totalTokens;
    bool isAlNum;
    string tokenString;
    TokenType makeToken(int c5); // this sucks figure out
    void incLineNum();


};
#endif //UNTITLED_SCANNER_H


