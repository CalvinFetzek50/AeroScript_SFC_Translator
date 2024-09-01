
#include <string>
#include "../classes/transition.hpp"

// function prototype
int nthOccurrence(const std::string& str, const std::string& findMe, int nth);

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
        std::any value = transition.getCurrentStep().stepVariableMap[targetVar];
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
        std::any value = transition.getCurrentStep().stepVariableMap[targetVar];
        transition.targetValue = value;

    }else{
        transition.targetVariable = "true";
        transition.targetValue = 1;
    }
}



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