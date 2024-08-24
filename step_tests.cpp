/* Test File to test methods implemented in the Step class  */

#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "step.hpp"

TEST_CASE("Test get and set Name", "[Step class]"){

    Step<int> testStep; 

    testStep.setName("test");
    REQUIRE(testStep.getName() == "test");
}

TEST_CASE("Test get and set Sequence", "[Step class]"){

    Step<int> testStep; 

    testStep.setSequence(5);
    REQUIRE(testStep.getSequence() == 5);
}


TEST_CASE("Test get and set Comment", "[Step class]"){

    Step<int> testStep; 

    std::string commentString = "this is a comment for the step";
    testStep.setName("test");
    testStep.setComment(commentString);
    REQUIRE(testStep.getComment() == commentString);
}

TEST_CASE("Test addVariable", "[Step class]"){

    Step<int> testStep; 
    
    REQUIRE(testStep.addVariable("temp", 0));
    REQUIRE(testStep.addVariable("angle", 50));
    REQUIRE(testStep.addVariable("distance",100));

    REQUIRE_FALSE(testStep.addVariable("temp",150));

}

TEST_CASE("Test upadateVariable", "[Step class]"){

    Step<int> testStep; 
    
    REQUIRE(testStep.addVariable("temp", 0));
    REQUIRE(testStep.addVariable("angle", 50));
    REQUIRE(testStep.addVariable("distance",100));

    REQUIRE(testStep.updateVariable("temp",150));
    REQUIRE(testStep.updateVariable("angle",200));

    REQUIRE_FALSE(testStep.updateVariable("dist",250));

}

TEST_CASE("Test copyMap", "[Step class]"){

    Step<int> testStep; 
    
    REQUIRE(testStep.addVariable("temp", 0));
    REQUIRE(testStep.addVariable("angle", 50));
    REQUIRE(testStep.addVariable("distance",100));

    Step<int> testStepCopy;

    REQUIRE(testStepCopy.copyMap(testStep));
    REQUIRE(testStepCopy.updateVariable("temp",150));


}