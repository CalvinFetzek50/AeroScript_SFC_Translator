#include "step.hpp"

#include <exception>

template<typename Unit>
std::string Step<Unit>::getName(){
    return stepName;
}

template<typename Unit>
void Step<Unit>::setName(std::string name){
    stepName = name;
}

template<typename Unit>
int Step<Unit>::getSequence(){
    return stepSequence;
}

template<typename Unit>
void Step<Unit>::setSequence(int sequence){
    stepSequence = sequence;
}


template<typename Unit>
std::string Step<Unit>::getComment(){
    return stepComment;
}

template<typename Unit>
void Step<Unit>::setComment(std::string comment){
    stepComment = comment;
}

template<typename Unit>
bool Step<Unit>::updateVariable(std::string variableName, Unit value){
    // get the corresponding key from the map and update the variable
    bool exists = false;

    if (stepVariableMap.find(variableName) == stepVariableMap.end()){
        // if element is not found in the map, return false.
        /* debug */
        std::cout << variableName << " Variable does not exist and cannot be updated. " << std::endl;
        /* debug */
        return false;
    }else{
        stepVariableMap[variableName] = value;
        
        /* debug */
        // std::cout << variableName << " is updated to: " << value << std::endl;
        /* debug */

        return true;
    }
    
}

template<typename Unit>
bool Step<Unit>::addVariable(std::string variableName, Unit value){
        if (stepVariableMap.find(variableName) == stepVariableMap.end()){
            // if the element is not found in the map, add to map
            stepVariableMap[variableName] = value;

            /* debug */
            // std::cout << variableName << " is set to: " << value << std::endl;
            /* debug */

            return true;    
        }else{
            // if element is duplicating, do nothing and return false

            /* debug */
            std::cout << variableName << " already exists. No change made to value."  << std::endl;
            /* debug */

            return false;
        }
    
}

template<typename Unit>
bool Step<Unit>::copyMap(Step<Unit> step){

    std::map<std::string, Unit> targetMap = step.stepVariableMap;
    std::map<std::string, Unit> originalMap = stepVariableMap;

    bool check;
    int checkCount = 0;
    
    for (auto const& x : targetMap){
        // add key (x.first) and value (x.second) pair to the current step class instantiation 
        check = addVariable(x.first, x.second);
        if (!check){
            checkCount++;
        } 
    }

    if (checkCount == 0){
        return true;
    }else{
        // if there was an existing map, do nothing and return false
        stepVariableMap = originalMap;
        return false;
    }
    
}