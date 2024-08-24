/* file to test Network class methods*/


#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "./classes/network.hpp"

TEST_CASE("test add and remove Node method", "[Network class]"){

    Network<int> network;

    Step<int> step;
    Transition<int> transition;
    Step<int> lastStep;

    step.addVariable("temp",100);
    step.setName("set temperature");
    step.setSequence(0);

    lastStep.addVariable("ange",50);
    lastStep.setName("set angle");
    lastStep.setSequence(1);

    transition.setCurrentStep(step);
    transition.setNextStep(lastStep);
    transition.setFunction("updateTemp");

    Node<int> node;

    node.sequence = 0;
    node.step = step;
    node.transition = transition;

    REQUIRE(network.addNode(node));
    REQUIRE(network.removeNode(0));
    REQUIRE_FALSE(network.removeNode(1));


}

TEST_CASE("test get Node method", "[Network class]"){

    Network<int> network;

    Step<int> step;
    Transition<int> transition;
    Step<int> lastStep;

    step.addVariable("temp",100);
    step.setName("set temperature");
    step.setSequence(0);

    lastStep.addVariable("angle",50);
    lastStep.setName("set angle");
    lastStep.setSequence(1);

    transition.setCurrentStep(step);
    transition.setNextStep(lastStep);
    transition.setFunction("updateTemp");

    Node<int> node;

    node.sequence = 0;
    node.step = step;
    node.transition = transition;

    REQUIRE(network.addNode(node));
    Node<int> newNode = network.getNode(0);
    REQUIRE(newNode.sequence == node.sequence);
    REQUIRE_THROWS(network.getNode(1));


}