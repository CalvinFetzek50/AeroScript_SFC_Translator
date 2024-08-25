
#include <string>
#include "../classes/command.hpp"
#include "../classes/network.hpp"
#include "../classes/step.hpp"
#include "../classes/transition.hpp"

template <typename Unit>
bool createNetwork(std::vector<Command>& commandVector, Step<Unit>& init_step, Network<Unit>& network){

    // variables used within this function
    int sequence = 0;

    // iterate through the functions using the parsed vector
    for (int idx = 0; idx < commandVector.size(); idx++){

        // generate initialized step
        Step<Unit> step;
        step.copyMap(init_step); 

        // generate transition
        Transition<Unit> transition;

        // generate a node to store the above steps and transitions
        Node<Unit> node;

        if (commandVector[idx].commandType == FUNCTION){

            // set sequence for step
            step.setSequence(sequence);
   
            // set step name
            std::string stepName = "Step_" + std::to_string(sequence);
            step.setName(stepName);

            // check if the type before the function is a comment. If comment, set up the comment to store in step
            if (commandVector[idx-1].commandType == COMMENT){
                std::string comment = commandVector[idx-1].commandString;
                step.setComment(comment);
            }

            // set current step using the step generated above
            transition.setCurrentStep(step);

            // set the function causing this transition
            std::string functionStr = commandVector[idx].commandString;
            transition.setFunction(functionStr);
            findAeroScriptFunction(functionStr,transition);
            
            // update the node
            node.sequence = sequence;
            node.step = step;
            node.transition = transition;

            // update sequence for next step
            sequence++;

            // update the network
            network.addNode(node);
        }
    }

    return true;
}