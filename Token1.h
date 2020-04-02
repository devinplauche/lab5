//
// Created by Devin Plauche on 1/17/20.
//
#include <string>
#ifndef TOKEN1_H
#define TOKEN1_H
using namespace std;
enum TokenType {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY,
    ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, ENDF
};
class Token {
public:
    Token()
    {
        value = UNDEFINED;
        lineNum = 1;
        stringLineNum = 1;
        name = "";
    }
    Token(TokenType madeToken, int lineNum1, string name1, int stringLineNum1)
    {
        name = name1;
        lineNum = lineNum1;
        value = madeToken;
        stringLineNum = stringLineNum1;
    }
    string name;
    TokenType value;
    int lineNum;
    int stringLineNum;
    string valueToString(TokenType value2);
    string tokenToString();
};


#endif //TOKEN_H