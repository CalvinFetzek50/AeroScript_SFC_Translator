/* file to test textReader  methods*/


#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include <iostream>
#include <fstream>
#include <exception>
#include <string>
#include "./functions/textParser.hpp"

// function prototype
std::string getType(AeroScriptType);

TEST_CASE("test textParser method","[textParser]"){

    // read AeroScript Source code into a single string
    std::string inputString;
    std::ifstream sourceFile ("../Input/Variables_and_Control_Flow_Example.txt");
    char c;

    if (sourceFile.is_open()){
        while (!sourceFile.eof()){
            sourceFile.get(c);
            inputString.push_back(c);
        }
        sourceFile.close();
    }else{
        std::cout << "Unable to open the input file";
    }

    // read text file by row
    std::vector<std::string> rowVector;
    rowVector = rowParser(inputString);

    // parse the text in to the Command Class
    std::vector<Command> commandVector;
    commandVector = rowIdentifier(rowVector);

    // combine comments
    combineComments(commandVector);

    /* debug */
    for (Command command : commandVector){
        std::cout  << getType(command.commandType) << ": " << command.commandString <<std::endl;
    }
}


/* helper function for debugging */

// VAR = 0, IF = 1, FOR = 2, COMMENT =3, OTHER = 4 etc...
std::string getType(AeroScriptType x){
    switch (x){
        case VAR:
            return "VAR";
            break;
        case COMMENT:
            return "COMMENT";
            break;
        case DECLARATION:
            return "DECLARATION";
            break;
        case WHILE:
            return  "WHILE";
            break;
        case FOREACH:
            return "FOREACH";
            break;
        case FOR:
            return "FOR";
            break;
        case FUNCTION_DEF:
            return "FUNCTION_DEF";
            break;
        case IF:
            return "IF";
            break;
        case REPEAT:
            return "REPEAT";
            break;
        case SWITCH:
            return "SWITCH";
            break;
        default:
            return "FUNCTION";
            break;
    }
};
