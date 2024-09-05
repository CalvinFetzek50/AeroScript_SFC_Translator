

#include <string>
#include <stack>
#include <cctype>
#include <vector>
#include "../classes/command.hpp"
#include "../classes/step.hpp"

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
            std::string variableName = command.commandString.substr(firstIdx,lastIdx-firstIdx);

            // get initial value type
            int firstTypeIdx = command.commandString.find(" as ") + 4;
            int lastTypeIdx = 0;
            for (int i = firstTypeIdx; i < command.commandString.length();i++){
                if (std::isspace(command.commandString[i])){
                    lastIdx = i;
                    break;
                }
            }

            std::string typeStr = command.commandString.substr(firstTypeIdx,lastTypeIdx-firstTypeIdx);
            
            // add to set containing all variable names
            step.namesSet.insert(variableName);

            // initialize variables 
            // when variable is not an array
            if (typeStr == "integer"){
                step.addVariable(variableName,0);    
            }else if (typeStr == "string"){
                step.addVariable(variableName,"");
            }
            
            // when variable is array
            
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