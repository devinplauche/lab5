//
// Created by Devin Plauche on 3/16/20.
//
#include <iostream>
#include "Parser.h"
#include <deque>
#include"Token1.h"
#include "Scanner1.h"
#include "Interpreter1.h"


int main(int argc, char* argv[]) {
    Scanner scannerObj(argv[1]);
    deque<Token> tokenVector;

    Token tokenObj(UNDEFINED, 1, "", 0);

    ifstream ifs; // just for checking if file is empty
    ifs.open(argv[1]);
    int c4;
    c4 = ifs.peek();
    if (!ifs.is_open()) {
        cout << "failed to open" << endl;
    }

    if (c4 != EOF) {

        while (c4 != EOF)
        {

            c4 = scannerObj.getChar();

            if (!isspace(char(c4))) {
                TokenType tokenValue = scannerObj.makeToken(c4);

                string valueString = scannerObj.getTString();
                int numLine = scannerObj.getLNum();
                int sNumLine = scannerObj.getStringLineNum();

                Token tempObj(tokenValue, numLine, valueString, sNumLine);
                if(tokenValue != COMMENT) {
                    tokenVector.push_back(tempObj);
                }


            } else if (c4 == '\n') {
                scannerObj.incLineNum();
            }


        }


        Parser parsing(tokenVector);


        bool succeeded = true;

        try {
            if (!tokenVector.empty() && tokenVector.at(0).value != ENDF ) {

                parsing.parse();

            }
            else {
                throw "empty";
            }
        }
        catch (char const *) {
            succeeded = false;
            cout << "Failure!" << endl;
            cout << "  " << parsing.parserTokens.front().tokenToString();
        }
        if (succeeded) {
            //cout << parsing.theProgram.toString(); // lab2 output, not necessary for Interpreter
        }



        Interpreter InterpreterObj(parsing.theProgram);
   
    

        InterpreterObj.evaluateRules(); // driver portion
        InterpreterObj.evaluateAllQueries();


    } else {

        cout << "Failure! \n(EOF,\"\",1)" << endl;

    }




    ifs.close();
    scannerObj.closeIfs();
    return 0;

}
