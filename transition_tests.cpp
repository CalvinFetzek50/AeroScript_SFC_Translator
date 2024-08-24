/* test cases to test the transition class */

#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "transition.hpp"

TEST_CASE(" Test get and set Step methods", "[Transition class]"){
    
    Step<int> testStep1;
    testStep1.addVariable("temp",10);
    testStep1.addVariable("angle",20);
    Step<int> testStep2;
    testStep2.addVariable("temp",50);
    testStep2.addVariable("angle",100);
    
    Transition<int> trans;

    trans.setCurrentStep(testStep1);
    trans.setNextStep(testStep2);

    REQUIRE(trans.getCurrentStep().stepVariableMap["temp"] == 10);
    REQUIRE(trans.getNextStep().stepVariableMap["temp"] == 50);


}

TEST_CASE(" Test get and set function methods", "[Transition class]"){
    
    
    Transition<int> trans;
    std::string functionString = "SetupTaskTargetMode";

    trans.setFunction(functionString);
    REQUIRE(trans.getFunction() == functionString);

}