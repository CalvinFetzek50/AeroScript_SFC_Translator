/* file to test textReader  methods*/


#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include <iostream>
#include <fstream>
#include <exception>
#include <set>
#include "./functions/textParser.hpp"
#include "./functions/variable_init.hpp"



TEST_CASE("test variable initialization methods","[variable_init]"){

    /* tested in testParser_tests.cpp */
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
    /* tested in testParser_tests.cpp */

    // combine comments
    combineComments(commandVector);
    
    // initialize the variables used in the script into a step class
    Step<std::string> initStep;
    findVariables(commandVector,initStep);

    // check if the array is incorporated correctly
    REQUIRE(initStep.stepVariableMap["$intArray"].size() == 10);


}