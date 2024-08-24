#include <iostream>
#include <fstream>
#include <string> 
#include <cctype>
#include <set>
#include <typeinfo>
#include <exception>
#include <stack>

#include "step.hpp"
#include "transition.hpp"
#include "network.hpp"
#include "Command.hpp"


#ifndef TEXTREADER_CPP
#define TEXTREADER_CPP





// function prototypes
int nthOccurrence(const std::string&, const std::string&, int);








/** This function initializes the variable map in the Step class
 * @param commandVector : a vector containing Command structs. This is the output of the rowIdentifier function
 * @param step : the initialized step class which contains all the variables used in the script.
 * @return returns true, if all variables have been added to the Step class, else returns false. */
template <typename Unit>
bool initializeVariables(std::vector<Command>& commandVector, Step<Unit>& step){

    // get all variables name 
    for (Command command : commandVector){
        if (command.commandType == VAR){
            // get index of "$" (beginning of variable name)
            int firstIdx = command.commandString.find("$");
            // get index of a space after the variable name (end of variable name)
            int lastIdx = 0;
            for (int i = 0; i < command.commandString.length();i++){
                if (std::isspace(command.commandString[i])){
                    lastIdx = i;
                    break;
                }
            }
            // get variable name
            std:: string variableName = command.commandString.substr(firstIdx,lastIdx-firstIdx);
            
            // add to set containing all variable names
            step.namesSet.insert(variableName);

            // initialize variables with nothing at first
            step.addVariable(variableName,"");
        }
    }

    // stack to store functions used to initialize variables
    std::stack<int> initStack;

    // initialize variables values
    for (int idx = 0; idx < commandVector.size(); idx++){

        Command command = commandVector[idx];

        if (command.commandType == FUNCTION){
            // get the first word of the string
            int firstSpaceIdx = 0;
            for (int i = 0; i < command.commandString.size(); i++){
                if(std::isspace(command.commandString[i])){
                    firstSpaceIdx = i;
                    break;
                } 
            }
            std::string firstWord = command.commandString.substr(0,firstSpaceIdx);
            
            // if the function began with a variable name, get the value after " = "
            std::string valueStr;
            std::string name;

            if (step.namesSet.find(firstWord) != step.namesSet.end()){

                // variables to track the location of the values
                name = firstWord;
                int equalSignIdx = 0;
                int endIdx = command.commandString.size()-1;

                // check the command String to get the substring after the "=" sign.  
                for (int i = 0; i < command.commandString.size();i++){
                    if(command.commandString[i] == '='){
                        equalSignIdx = i;
                        std::string afterEqStr = command.commandString.substr(equalSignIdx+1,endIdx-equalSignIdx);
                        // get the value after the space
                        for (int j = 0; j < afterEqStr.size();j++){
                            if (!std::isspace(afterEqStr[j])){
                                // store the value as an string in valueStr
                                valueStr = afterEqStr.substr(j,afterEqStr.size()-j); 
                                break;
                            }
                        }
                    }
                }
                
                // store values as string 
                step.updateVariable(name,valueStr);

                // if the variable was initialized, store the index of the function into the stack
                initStack.push(idx);
            }

        }

    }

    // remove the functions used to initialize variables from the commandVector
    int initStackSize = initStack.size();
    for (int i = 0; i < initStackSize;i++){
        int removeIdx = initStack.top();
        commandVector.erase(commandVector.begin()+removeIdx);
        initStack.pop();
    } 
    
    return true;
} 

/** function to combine for loops into one group
 * @param commandVector : a vector containing Command structs. This is the output of the rowIdentifier function
 * @param step : the initialized step class which contains all the variables used in the script.
 */
template <typename Unit>
void combineForLoops(std::vector<Command>& commandVector, Step<Unit>& step){
    
    // combine lines that go under the same for loop    
    std::set<std::string> forLoopsSet;

    // create a set with all potential combinations that indicate a beginning of the for loop
    for (std::string name : step.namesSet){
        std::string example = "for " + name;
        forLoopsSet.insert(example);
    }

    // variables used within this loop
    bool isForLoop = false; // boolean to identify the loop is passing through the for loop
    int beginIdx = 0;
    int endIdx = 0;
    std::stack<int> idxStack;

    // combined for loop lines into one string
    for (int idx = 0; idx < commandVector.size();idx++){
        
        // identify the beginning and end of the for loop
        if (commandVector[idx].commandType == FUNCTION){

            std::string currentStr = commandVector[idx].commandString;

            for (std::string item : forLoopsSet){
                if (currentStr.find(item) != std::string::npos){
                // identify the beginning of the for loop
                isForLoop = true;
                beginIdx = idx;
                }
            }

            if ((currentStr == "end") && (isForLoop)){
                // identify the end of the for loop
                isForLoop = false;
                endIdx = idx;

                // update the vector
                std::string combinedStr = "";
                for (int i = beginIdx; i < endIdx; i++){
                    if (commandVector[i].commandType == COMMENT){
                        // if there were comments within the vector, clarify comments with "//" attached to the beginning
                        combinedStr += ("//" + commandVector[i].commandString + "\n");

                    }else{
                        // if the command type is of function add the string directly
                        combinedStr += (commandVector[i].commandString + " ");
                    }

                    idxStack.push(i);
                }
                commandVector[endIdx].commandString = combinedStr +commandVector[endIdx].commandString;
                
            }
        }
    }

    // erase redundant function commands for the for loop
    int idxStackSize = idxStack.size();
    for (int i = 0; i < idxStackSize; i++){
        int erasedIdx = idxStack.top();
        commandVector.erase(commandVector.begin()+erasedIdx);
        idxStack.pop();
    }
}

/** function to combine while loops
 * @param commandVector : a vector containing Command structs. This is the output of the rowIdentifier function
 * @param step : the initialized step class which contains all the variables used in the script. */
template <typename Unit>
void combineWhileLoops(std::vector<Command>& commandVector, Step<Unit>& step){

    // combine lines that go under the same for loop    
    std::set<std::string> whileLoopsSet;

    // create a set with all potential combinations that indicate a beginning of the for loop
    for (std::string name : step.namesSet){
        std::string example = "while (" + name;
        whileLoopsSet.insert(example);
    }

    // bool to flag the beginning of the while loop
    bool isWhile = false;
    int beginIdx = 0;
    int endIdx = 0;
    std::stack<int> idxStack;

    // flag the beginning of the while loop
    for (int i = 0; i < commandVector.size();i++){

        if (commandVector[i].commandType == FUNCTION){

            std::string currentStr = commandVector[i].commandString;
            
            // loop through set created above to find while loop statement
            for (std::string item : whileLoopsSet){
                if (currentStr.find(item) != std::string::npos){
                    // true when string matches row to indicate the beginning of the while loop
                    isWhile = true;
                    beginIdx = i;
                }
            }

            // identify the end of the while loop
            if ((currentStr == "end") & (isWhile)){
                isWhile = false;
                endIdx = i;

                // update the vector
                std::string combinedStr = "";

                for (int i = beginIdx; i < endIdx; i++){
                    if (commandVector[i].commandType == COMMENT){
                        // if there were comments within the vector, clarify comments with "//" attached to the beginning
                        combinedStr += ("//" + commandVector[i].commandString + "\n");

                    }else{
                        // if the command type is of function add the string directly
                        combinedStr += (commandVector[i].commandString + " ");
                    }

                    idxStack.push(i);
                }
                commandVector[endIdx].commandString = combinedStr +commandVector[endIdx].commandString;
            }   
        }
    }

    // erase redundant function commands for the loop
    int idxStackSize = idxStack.size();
    for (int i = 0; i < idxStackSize; i++){
        int erasedIdx = idxStack.top();
        commandVector.erase(commandVector.begin()+erasedIdx);
        idxStack.pop();
    }
}


/** function to iterate through each line of AeroScript Source code and create a network of Nodes consisting of both Step and Transition
 * @param commandVector std::vector of type Command. This vector is modified after running initializeVariables().
 * @param init_step Step<Unit> class with the variable map filled in. This class is modified after running initializeVariables().
 * @param network Network class to store all steps and transitions
 * @return returns true if all lines were processed and network is completed. False if not. */
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

/** function to determine the Aeroscript function imported into the function Class.
 * It will update the targetVariable and targetValue of the transition Class.
 * @param functionStr the string containing the AeroScript function name
 * @param transition the transition class used to update the targetVariable and targetValue */
template <typename Unit>
void findAeroScriptFunction(const std::string functionStr, Transition<Unit>& transition){

    if(functionStr.find("for $") != std::string::npos){
        // when a for loop is identified
        // target variable will be the first argument
        int beginIdx = functionStr.find('$');
        int endIdx;
        for (int i = beginIdx;i < functionStr.length();i++){
            if (std::isspace(functionStr[i])){
                // get next space after '$'
                endIdx = i;
                break;
            }
        }
        std::string targetVar = functionStr.substr(beginIdx,endIdx-beginIdx); 
        transition.targetVariable = targetVar;

        // target value will be the second argument
        beginIdx = nthOccurrence(functionStr,"$",2);
        for (int i = beginIdx;i < functionStr.length();i++){
            if (std::isspace(functionStr[i])){
                // get next space after '$'
                endIdx = i;
                break;
            }
        }
        targetVar = functionStr.substr(beginIdx,endIdx-beginIdx);
        Unit value = transition.getCurrentStep().stepVariableMap[targetVar];
        transition.targetValue = value;

    } else if(functionStr.find("MoveLinear($") != std::string::npos){
        // when the move linear function is identified (not in for loop)
        // target variable will be the first argument
        int beginIdx = functionStr.find('$');
        int endIdx = functionStr.find(',');
        std::string targetVar = functionStr.substr(beginIdx,endIdx-beginIdx); 
        transition.targetVariable = targetVar;
        
        // target value will be the second argument
        beginIdx = nthOccurrence(functionStr,"$",2);
        endIdx = nthOccurrence(functionStr,",",2);
        targetVar = functionStr.substr(beginIdx,endIdx-beginIdx);
        Unit value = transition.getCurrentStep().stepVariableMap[targetVar];
        transition.targetValue = value;

    }else{
        transition.targetVariable = "true";
        transition.targetValue = 1;
    }
}

/********************/
/* Helper Functions */
/********************/

/**  function to find the nth occurrence of hte character in a string */
int nthOccurrence(const std::string& str, const std::string& findMe, int nth)
{
    int  pos = 0;
    int  cnt = 0;

    while( cnt != nth )
    {
        pos+=1;
        pos = str.find(findMe, pos);
        if ( pos == std::string::npos )
            return -1;
        cnt++;
    }
    return pos;
}


/** function to write the network onto a csv file
 * @param filename filename of the output file as std::string
 * @param network Network class that contains the information of the AeroScript Source Code */
template <typename Unit>
void write_csv(std::string filename, Network<Unit> network){
    
    // Create an output filestream object
    std::ofstream myFile(filename);

    myFile << "start" << "\n";
    myFile << "|";
    myFile << "\n";
    
    // Send data to the stream
    for(int i = 0; i < network.getSize(); ++i){

        Node<Unit> currentNode = network.getNode(i); 

        // add step name
        myFile << "Step_" + std::to_string(currentNode.sequence);
        myFile << ",,";

        // add comments
        myFile << "N,";
        //myFile << currentNode.step.getComment();
        //myFile << "\n";

        // add functions
        // add double quotes into the beginning and end of string to ouput into csv file
        myFile << "\"" + currentNode.transition.getFunction() + "\"";
        myFile << "\n";
        
        // add transtions
        myFile << "|" << ",";
        myFile << currentNode.transition.targetVariable + " = " + currentNode.transition.targetValue;
        myFile << "\n";

    }

    myFile << "end";
    
    // Close the file
    myFile.close();
}


#endif 