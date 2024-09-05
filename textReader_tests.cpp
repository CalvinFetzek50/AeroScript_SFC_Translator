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
#include "./functions/combine_text.hpp"
#include "./functions/network_init.hpp"
#include "./functions/match_functions.hpp"
#include "./functions/write_csv.tpp"



TEST_CASE("test textReader method","[textReader]"){

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

    // initialize the variables used in the script into a step class
    Step<std::string> initStep;
    REQUIRE(initializeVariables(commandVector,initStep));

    // combine for loops
    combineForLoops(commandVector,initStep);

    // combine while loops
    combineWhileLoops(commandVector,initStep);

    // create the network of nodes consisting of steps and transitions
    Network<std::string> testNetwork;
    REQUIRE(createNetwork(commandVector, initStep,testNetwork));

    /* debug */
    for (int i = 0; i < testNetwork.getSize();i++){

        Node<std::string> node = testNetwork.getNode(i);
        
        std::cout << "Name: " <<node.step.getName() << std::endl;
        std::cout << "Comment: " << node.step.getComment() << std::endl;
        std::cout << "function: " <<node.transition.getFunction() << std::endl;
        std::cout << "****************" << std::endl;
         
    }

    // write output to CSV
    write_csv("../Output/Output_ControlFlow.csv", testNetwork);

}