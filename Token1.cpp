//
// Created by Devin Plauche on 1/18/20.
//

#include "Token1.h"
#include <string>
using namespace std;

string Token::tokenToString()
{
    string returnString = "(";
    returnString += valueToString(value);
    returnString += ",\"";
    returnString += name;
    returnString += "\",";
    if(value == COMMENT || value == (STRING) || value == UNDEFINED)
    {
        returnString += to_string(stringLineNum);
    }
    else {
        returnString += to_string(lineNum);
    }

    returnString += ")\n";
    return returnString;
}
string Token::valueToString(TokenType value3)
{
    switch(value3) { //could use to set name
        case ENDF:
            return "EOF";
            break;
        case COMMA:
            return "COMMA";
            break;
        case PERIOD:
            return "PERIOD";
            break;
        case Q_MARK:
            return "Q_MARK";
            break;
        case LEFT_PAREN:
            return "LEFT_PAREN";
            break;
        case RIGHT_PAREN:
            return "RIGHT_PAREN";
            break;
        case COLON:
            return "COLON";
            break;
        case COLON_DASH:
            return "COLON_DASH";
            break;
        case MULTIPLY:
            return "MULTIPLY";
            break;
        case ADD:
            return "ADD";
            break;
        case SCHEMES:
            return "SCHEMES";
            break;
        case FACTS:
            return "FACTS";
            break;
        case RULES:
            return "RULES";
            break;
        case QUERIES:
            return "QUERIES";
            break;
        case ID:
            return "ID";
            break;
        case STRING:
            return "STRING";
            break;
        case COMMENT:
            return "COMMENT";
            break;
        case UNDEFINED:
            return "UNDEFINED";
            break;
    }
    return "ERROR";
}


