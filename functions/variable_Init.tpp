

#include <string>
#include <iostream>
#include <stack>
#include <cctype>
#include <vector>
#include "../classes/command.hpp"
#include "../classes/step.hpp"

template <typename Unit>
void findVariables(std::vector<Command>& commandVector, Step<Unit>& step){

    // get all variables name 
    for (Command command : commandVector){
        if (command.commandType == VAR){
            // get index of "$" (beginning of variable name)
            int firstIdx = command.commandString.find("$");
            // get index of a space after the variable name (end of variable name)
            int lastIdx = command.commandString.length();
            for (int i = 0; i < command.commandString.length();i++){
                if (std::isspace(command.commandString[i])){
                    lastIdx = i;
                    break;
                }
            }

            // get variable name
            std::string variableName = command.commandString.substr(firstIdx,lastIdx-firstIdx);
            bool isArray = false;

            // when variable is an array, remove the "[XX]" from the variable name
            if (variableName.find("[") != std::string::npos){
                lastIdx = variableName.find("[");
                variableName = variableName.substr(0,lastIdx);
                isArray = true;
            }

            // get initial value type
            int firstTypeIdx = command.commandString.find(" as ") + 4;
            int lastTypeIdx = command.commandString.length();
            for (int i = firstTypeIdx; i < command.commandString.length();i++){
                if (std::isspace(command.commandString[i])){
                    lastTypeIdx = i;
                    break;
                }
            }

            std::string typeStr = command.commandString.substr(firstTypeIdx,lastTypeIdx-firstTypeIdx);

            // get initial value
            std::string valueStr = ""; 

            if (command.commandString.find("=") != std::string::npos){
                int firstValueIdx = command.commandString.find("=") +1;
                int lastValueIdx = command.commandString.length();
                for (int i = firstTypeIdx; i < command.commandString.length();i++){
                    if (std::isspace(command.commandString[i])){
                        lastTypeIdx = i;
                        break;
                    }
                }
                // update value string when the variable is declared with an initialization
                valueStr = command.commandString.substr(firstValueIdx,lastValueIdx-firstValueIdx);
            }
            
            // add to set containing all variable names
            step.namesSet.insert(variableName);

            // Add variable to the variable map
            if (!isArray){
                // when variable is not an array
                if (typeStr == "integer"){
                    if (valueStr.length() != 0){
                        // if variable is initialized with an value
                        step.addVariable(variableName,std::stoi(valueStr),isArray);   
                    }else{
                        // if variable is not initialized with an value, initialize with 0
                        step.addVariable(variableName,0,isArray);   
                    }
                     
                }else if (typeStr == "string"){
                    step.addVariable(variableName,valueStr,isArray);
                }else{
                    // default : initialize variable as empty string
                    step.addVariable(variableName,valueStr,isArray);
                }              
            }

            if(isArray){
                // when variable is an array
                if (typeStr == "integer"){
                    int startVarIdx = 0;
                    int endVarIdx = 0;
                    for (int i = 0; i < valueStr.length();i++){
                        if (valueStr[i] == '['){
                            startVarIdx = i+1;
                        }else if (valueStr[i] == ']'){
                            endVarIdx = i;
                            // get inidividual value from array
                            std::string varStr = valueStr.substr(startVarIdx,endVarIdx-startVarIdx);
                            // store individual value from array into the variable map
                            step.addVariable(variableName,std::stoi(varStr),isArray);

                            // end loop
                            break;

                        }else if (valueStr[i] == ','){
                            endVarIdx = i;
                            // get inidividual value from array
                            std::string varStr = valueStr.substr(startVarIdx,endVarIdx-startVarIdx);
                            // store individual value from array into the variable map
                            step.addVariable(variableName,std::stoi(varStr),isArray);

                            //update the start index
                            startVarIdx = endVarIdx+1;
                        }
                    }
                }else if (typeStr == "string"){
                    int startVarIdx = 0;
                    int endVarIdx = 0;
                    for (int i = 0; i < valueStr.length();i++){
                        if (valueStr[i] == '['){
                            startVarIdx = i+1;
                        }else if (valueStr[i] == ']'){
                            endVarIdx = i;
                            // get inidividual value from array and remove the "" from each string
                            std::string varStr = valueStr.substr(startVarIdx,endVarIdx-startVarIdx);

                            /* debug */
                            std::cout << varStr.length() << std::endl;

                            // store individual value from array into the variable map
                            step.addVariable(variableName,varStr,isArray);

                            // end loop
                            break;

                        }else if (valueStr[i] == ','){
                            endVarIdx = i;
                            // get inidividual value from array and remove the "" from each string
                            std::string varStr = valueStr.substr(startVarIdx,endVarIdx-startVarIdx);
                            
                            // store individual value from array into the variable map
                            step.addVariable(variableName,varStr,isArray);

                            //update the start index
                            startVarIdx = endVarIdx+2;
                        }
                    }
                }
            }
   

            /* debug */
            std::cout << "Added " << variableName << std::endl; 
        }
    }    
} 

template <typename Unit>
void initializeVariables(std::vector<Command>& commandVector, Step<Unit>& step){

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

                // if the variable was initialized, store the row index of the function into the stack
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
    

}