#include "step.hpp"
#include "../functions/any_to_String.hpp"
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
bool Step<Unit>::updateVariable(std::string variableName, std::any value){
    // get the corresponding key from the map and update the variable
    if (stepVariableMap.find(variableName) == stepVariableMap.end()){
        // if element is not found in the map, return false.

        /* debug */
        std::cout << variableName << " Variable does not exist and cannot be updated. " << std::endl;
        /* debug */

        return false;
    }else{
        if (stepVariableMap[variableName].empty()){
            // if variable value is an empty vector add to vector
            stepVariableMap[variableName].push_back(value);
        }else{
            // if variable value is not empty, remove last element and add new element
            stepVariableMap[variableName].pop_back();
            stepVariableMap[variableName].push_back(value);
        }
    }
        
        
        /* debug */
        std::cout << variableName << " is updated to: " << any_to_string(value) << std::endl;
        /* debug */

        return true;
    
}

template<typename Unit>
bool Step<Unit>::addVariable(std::string variableName, std::any value, bool isArray){
        if ((stepVariableMap.find(variableName) == stepVariableMap.end())&&(!isArray)){
            // if the element is not found in the map, add to map
            stepVariableMap[variableName].push_back(value);

            /* debug */
            // std::cout << variableName << " is set to: " << value << std::endl;
            /* debug */

            return true;    
        }else if (isArray){
            // if the element is part of an array, add to array
            stepVariableMap[variableName].push_back(value);

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

    std::map<std::string, std::vector<std::any>> targetMap = step.stepVariableMap;
    std::map<std::string, std::vector<std::any>> originalMap = stepVariableMap;

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