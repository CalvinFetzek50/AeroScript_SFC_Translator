

#include <stack>
#include <string>
#include "../classes/command.hpp"
#include "../classes/step.hpp"

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