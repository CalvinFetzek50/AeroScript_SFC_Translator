/* file to test textReader  methods*/


#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "textReader.hpp"

// function prototype
void getType(AeroScriptType);

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


/* helper function for debugging */

// VAR = 0, IF = 1, FOR = 2, COMMENT =3, OTHER = 4
void getType(AeroScriptType x){
    switch (x){
        case VAR:
            std::cout << "VAR";
            break;
        case IF:
            std::cout <<"IF";
            break;
        case COMMENT:
            std::cout <<"COMMENT";
            break;
        case DECLARATION:
            std::cout <<"DECLARATION";
            break;
        default:
            std::cout <<"FUNCTION";
            break;
    }
};