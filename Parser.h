//
// Created by Devin Plauche on 1/28/20.
//
#include "Token1.h"
#include "Datalogprogram.h"
#include <string>
#include <iostream>
#include "Scanner1.h"
#include "Rule.h"
#include "Predicate.h"
#include <deque>
#ifndef PARSER_H
#define PARSER_H
 class Parser {
public:
    Parser(deque<Token> parserTokensIn) {

        for(size_t i = 0; i < parserTokensIn.size(); i++)
        {
            parserTokens.push_back(parserTokensIn.at(i));
        }
    }

    deque<Token> parserTokens;
    Datalog theProgram;
    Rule ruleObj;
    //Predicate newPred(string newName);
    void match(TokenType input);
    void parse();
    void parseFact();
    void parseRule();
    void parseQuery();
    void parseScheme();
    void parseFactList();
    void parseRuleList();
    void parseQueryList();
    void parseSchemeList();
    void parseHeadPredicate(Rule &tempRule);
    void parsePredicate(Rule &tempRule);
    void parseQPredicate();
    void parsePredicateList(Rule &tempRule);
    void parseParameterList(Predicate &paramList);
    void parseStringList(Predicate &stringPred);
    void parseIdList(Predicate &predHere);
    void parseParameter(Predicate &forParams);
    void parseExpression(Predicate &expressionPred);
    void parseOperator(Predicate &opParam);

    string tokenString;

    Token parserToken;

};
#endif //LAB2_PARSER_H
