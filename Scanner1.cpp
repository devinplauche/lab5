//
// Created by Devin Plauche on 1/18/20.
//
#include <fstream>
#include <cctype>
#include <iostream>
#include "Scanner1.h"
int Scanner::getStringLineNum() {
    return stringLineNum;
}
void Scanner::closeIfs()
{
    ifs.close();
}
void Scanner::incLineNum() {
    lineNum++;
}
int Scanner::getLNum() {
    return lineNum;
}
string Scanner::getTString()
{
    return tokenString;
}
int Scanner:: getTotalTokens() {
    return totalTokens;
}
int Scanner::getChar()
{
    c = ifs.get();
    return c;
}
TokenType Scanner::makeToken(int c1)
{
    switch(c1) {
        case EOF:
            tokenString = "";
            return ENDF;
        case ',':
            tokenString = ",";
            return COMMA;
            break;
        case '.':
            tokenString = ".";
            return PERIOD;
            break;
        case '?':
            tokenString = "?";
            return Q_MARK;
            break;
        case '(':
            tokenString = "(";
            return LEFT_PAREN;
            break;
        case ')':
            tokenString = ")";
            return RIGHT_PAREN;
            break;
        case ':':
            if (ifs.peek() == '-') {
                ifs.get(); // make sure counter is in right spot
                tokenString = ":-";
                return COLON_DASH;
            } else {
                tokenString = ":";
                return COLON;
            }
            break;

        case '*':
            tokenString = "*";
            return MULTIPLY;
            break;
        case '+':
            tokenString = "+";
            return ADD;
            break;
        case '\'':
            stringLineNum = lineNum;
            tokenString = ""; // reset
            tokenString = "\'";
            bool escape = false;
            int c2 = 'a';
            while (1) {

                c2 = ifs.get();
                escape = true;
                if (c2 == EOF) {
                    return UNDEFINED;
                    break;
                }


                if (c2 == '\'' && ifs.peek() == '\'')
                {
                    escape = false;
                    //break;
                    ifs.get(); // gets second apostrophe
                    //c2 = ifs.get(); //gets character after second apostrophe
                    tokenString += "\'";

                }
                if(c2 == '\'' && ifs.peek() != '\'' && escape)
                {
                    break;
                }
                if (c2 == '\n') { // check may not be right IDK
                    incLineNum();
                }

                tokenString += c2; // adjust for individual type // CHECK

            }// adjust to read until next quote // account for escape sequences of apostrophes
            tokenString += '\'';
            return STRING;
            break;

    }

    if(char(c1) == '#' && ifs.peek() != '|') {
        tokenString = ""; //reset
        tokenString += c1;
        int c3 = ifs.get();
        tokenString += c3;
        while (c3 != '\n') {
            c3 = ifs.peek(); // check logic
            if (c3 == EOF) {
                break;
            }
            if(c3 != '\n') {
                tokenString += ifs.get();
            }
        }
        stringLineNum = lineNum;
        return COMMENT;
    }
    if (char(c1) == '#' && ifs.peek() == '|') {
        stringLineNum = lineNum;
        tokenString = "#|";
        ifs.get(); // gets '|'
        string checkBlock;
        string endBlock = "|#";
        int isEOF = 0;
        while (checkBlock != endBlock) // block comment
        {
            isEOF = ifs.peek();
            if (isEOF == EOF) {
                return UNDEFINED;
                break;
            }

            if (isEOF == '\n') {
                incLineNum();

            }

            checkBlock = "";
            checkBlock += ifs.peek();
            tokenString += ifs.get();
            checkBlock += ifs.peek();


        }
        tokenString += ifs.get();
        return COMMENT;
    }
    if (isalpha(char(c1))) {
        tokenString = "";
        tokenString += char(c1);
        while (isalnum(ifs.peek())) { // basically the else case // handle line numbers
            tokenString += ifs.get();
        }
        if (tokenString == "Schemes") {

            return SCHEMES; // adjust input counter
        }
        else if (tokenString == "Rules") {

            return RULES;
        }
        else if (tokenString == "Facts") {
            return FACTS;
        }
        else if(tokenString == "Queries")
        {
            return QUERIES;
        }

        return ID;
    }


    tokenString = c1;
    stringLineNum = lineNum;
    return UNDEFINED;

}
// Created by Devin Plauche on 1/20/20.
//



