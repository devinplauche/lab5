//
// Created by Devin Plauche on 1/28/20.
//
#include "Parser.h"
#include "Scanner1.h"
#include <iostream>

void Parser::match(TokenType input) {

    if(input == parserTokens.front().value) {
        parserTokens.pop_front();
    }
    else if(parserTokens.front().value != input) { // check second condition
        cout << parserTokens.front().name << input << endl;
        throw "Failure!";;
    }

}


void Parser::parse() {

    if (parserTokens.front().value == SCHEMES) {

        match(SCHEMES);
        match(COLON);
        parseSchemeList(); // FIXME
    } if (parserTokens.front().value == FACTS) { // change else into functions

        match(FACTS);
        match(COLON);
        if(parserTokens.front().value != RULES) { // condition for empty section
            parseFactList();
        }

    }if (parserTokens.front().value == RULES) {

        match(RULES);
        match(COLON);
        if(parserTokens.front().value != QUERIES) {
            parseRuleList();
        }
    } if (parserTokens.front().value == QUERIES) {

        match(QUERIES);
        match(COLON);
        parseQuery();
        if(parserTokens.front().value != ENDF) {
            parseQueryList();
        }
        else {
            match(ENDF);
           //cout << "Success!" << endl; //reached EOF succesfully
        }
    }
    /*else {

       throw "Failure!"; // get type and line number; // should I throw here?
    }*/

}
void Parser::parseScheme() {
    Predicate newPred(parserTokens.front().name);

    match(ID);

    match(LEFT_PAREN);
    newPred.addParam(parserTokens.front().name);
    match(ID);

    if(parserTokens.front().value == COMMA) {
        parseIdList(newPred);
    }
    match(RIGHT_PAREN);
    theProgram.schemesVector.push_back(newPred);
}
void Parser::parseSchemeList() {
    parseScheme();
    if(parserTokens.front().value != FACTS) {
        parseSchemeList();
    }
    else {

        parse();
    }
}
void Parser::parseFact() {
    Predicate newPred(parserTokens.front().name);

    match(ID);
    match(LEFT_PAREN);
    newPred.addParam(parserTokens.front().name);
    match(STRING);
    newPred.paramVector.back().isConstant = true;
    if(parserTokens.front().value != RIGHT_PAREN) {
        parseStringList(newPred);
    }
    match(RIGHT_PAREN);
    match(PERIOD);

    theProgram.factsVector.push_back(newPred);
}
void Parser::parseFactList() {

    parseFact();
    if(parserTokens.front().value != RULES) {
        parseFactList();
    }
    else {
        parse();
    }

}
void Parser::parseRule() {
    Rule tempRule;
    parseHeadPredicate(tempRule);
    match(COLON_DASH);
    parsePredicate(tempRule);
    if(parserTokens.front().value != PERIOD) {
        parsePredicateList(tempRule); // put conditional before to avoid errors
    }

        match(PERIOD);

    theProgram.rulesVector.push_back(tempRule);
}
void Parser::parseRuleList() {
    parseRule();
    if(parserTokens.front().value != QUERIES) {
        parseRuleList();
    }
    else {
        parse();
    }
}

void Parser::parseQuery() {
    parseQPredicate(); // change to accept pointer
    match(Q_MARK);
}
void Parser::parseQueryList() {
    parseQuery();
    if(parserTokens.front().value != ENDF) {
        parseQueryList();
    }
    else {
        match(ENDF);

    }

}
void Parser::parseQPredicate() {
    Predicate newPred(parserTokens.front().name);
    match(ID);
    match(LEFT_PAREN);
    parseParameter(newPred);
    if(parserTokens.front().value != RIGHT_PAREN) {
        parseParameterList(newPred); // CHECK! probably doesn't work
    }
    match(RIGHT_PAREN);
    theProgram.queriesVector.push_back(newPred);// create right objects and add to rule
}

void Parser::parseHeadPredicate(Rule &tempRule) {
    Predicate newPred(parserTokens.front().name);
    match(ID);

    match(LEFT_PAREN);
    newPred.addParam(parserTokens.front().name);
    match(ID);

    if (parserTokens.front().value != RIGHT_PAREN) {
        parseIdList(newPred);
    }
    match(RIGHT_PAREN);
    // create rule left object and create rule
    tempRule.leftPredicate.push_back(newPred); // should only happen once, else error

}
void Parser::parsePredicate(Rule &tempRule) {
    Predicate newPred(parserTokens.front().name);
    match(ID);
    match(LEFT_PAREN);
    parseParameter(newPred);
    if(parserTokens.front().value != RIGHT_PAREN) {
        parseParameterList(newPred); // check
    }
    match(RIGHT_PAREN);
    tempRule.rightPredicates.push_back(newPred);// create right objects and add to rule
}
void Parser::parsePredicateList(Rule &tempRule) {

    match(COMMA);
    parsePredicate(tempRule);
    if (parserTokens.front().value != PERIOD) {
            parsePredicateList(tempRule);
    }


}
void Parser::parseParameterList(Predicate &paramList) {

    match(COMMA);
    parseParameter(paramList);
    if(parserTokens.front().value != RIGHT_PAREN) {
        parseParameterList(paramList);
    }
    // do nothing for lambda
}
void Parser::parseStringList(Predicate &stringPred) {

    match(COMMA);
    stringPred.addParam(parserTokens.front().name);
    match(STRING);
    stringPred.paramVector.back().isConstant = true; // back is correct
    if(parserTokens.front().value != RIGHT_PAREN) {
        parseStringList(stringPred);
    }
    // do nothing for lambda
}
void Parser::parseIdList(Predicate &predHere) {
    match(COMMA);
    predHere.addParam(parserTokens.front().name);

    match(ID);

    if(parserTokens.front().value == COMMA) {
        parseIdList(predHere);
    }

        // do nothing (lambda)

}
void Parser::parseParameter(Predicate &forParams) {
    if(parserTokens.front().value == STRING) {
        forParams.addParam(parserTokens.front().name);
        match(STRING);
        forParams.paramVector.back().isConstant = true;
    }
    else if(parserTokens.front().value == ID) {
        forParams.addParam(parserTokens.front().name);
        match(ID);
    }
    else if(parserTokens.front().value == LEFT_PAREN) {
        parseExpression(forParams);
    }
}
void Parser::parseExpression(Predicate &expressionParam) {
    //match(LEFT_PAREN);
    size_t numLParen = 0;
    expressionParam.addParam("");
    while (parserTokens.front().value != RIGHT_PAREN) { // should never hit, but just in case
        expressionParam.paramVector.back().paramValue += "(";
        match(LEFT_PAREN);
        numLParen++;
        expressionParam.paramVector.back().paramValue += parserTokens.front().name;
        match(ID);

        parseOperator(expressionParam);
        if(parserTokens.front().value == ID)
        {
            expressionParam.paramVector.back().paramValue += parserTokens.front().name;
            match(ID);
            break;
        }
    }
    for(size_t i = 0; i < numLParen; i++) {

        expressionParam.paramVector.back().paramValue += ")";
        match(RIGHT_PAREN);

    }



}
void Parser::parseOperator(Predicate &operatorParam) { //should treat as Param?
    if(parserTokens.front().value == ADD) {

        match(ADD);
        operatorParam.paramVector.back().paramValue += '+';

    }
    else if(parserTokens.front().value == MULTIPLY) {

        match(MULTIPLY);
        operatorParam.paramVector.back().paramValue += '*';
    }
    else {
        throw "bad operator";
    }

}