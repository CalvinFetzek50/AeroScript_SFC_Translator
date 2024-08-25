#include "../classes/command.hpp"

std::vector<std::string> rowParser(std::string sourceScript){

    std::vector<std::string> rowsVector;
    std::string line = "";

    // store each line in a vector of strings
    for (int i =0; i < sourceScript.length(); i++){
        if ((sourceScript[i] == '\n') || (sourceScript[i] == '\r')){
            // reset  string once reaching the end of the line.
            if (line.length() > 0){
                rowsVector.push_back(line);
            }
            line = "";
        }else if (sourceScript[i] == '\t'){
            // ignore tabs 
        }else{
            line += sourceScript[i];
        }
    }
    return rowsVector;   
}

void combineComments(std::vector<Command>& commandVector){
    for (int i = 0; i < commandVector.size(); i++){
        if ((commandVector[i].commandType == COMMENT) && (commandVector[i+1].commandType == COMMENT)){
            commandVector[i+1].commandString  = commandVector[i].commandString + commandVector[i+1].commandString;
            // erase the item after adding to the next item 
            commandVector.erase(commandVector.begin()+i);
        }
    }
}

std::vector<Command> rowIdentifier(std::vector<std::string> rowVector){

    std::vector<Command> parsedVector;

    for (int i = 0; i < rowVector.size(); i++){
        // store string for each row
        std::string targetString = rowVector[i]; 

        // ignore first spaces
        int firstLetter = 0;
        for (char c : targetString){
            if (std::isspace(c)){
                firstLetter++;
            }else{
                break;
            }
        }
        targetString = targetString.substr(firstLetter,targetString.length()-firstLetter);

        // initialize a AeroScript Command struct for each row
        Command target; 

        // identify the type of the command
        if((targetString[0] == '/') && (targetString[0+1] == '/')){
            // Identify comments by checking the first two characters of the string if it is "//"
            target.commandType = COMMENT;
            target.commandString = targetString.substr(2,targetString.length()-2);
            
        }else if ((targetString[0] == 'v') && (targetString[0+1] == 'a')&& (targetString[0+2] == 'r')){
            // Identify variables by chacking for the word "var $"
            target.commandType = VAR;
            target.commandString = targetString.substr(4,targetString.length()-4);

        }else if (targetString == "program") {
            // identify program declaration by searching for "program"
            target.commandType = DECLARATION;
            target.commandString = targetString;

        }else{
            target.commandType = FUNCTION;
            target.commandString = targetString;
        }
        // add generated command struct to the vector
        parsedVector.push_back(target);   
    }
    
    // combine comments
    combineComments(parsedVector);

    return parsedVector;
}