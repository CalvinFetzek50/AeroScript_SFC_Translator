#ifndef COMMAND_CPP
#define COMMAND_CPP

#include <string>

// Enumerator representing AeroScript Source code types
enum AeroScriptType {VAR, COMMENT, DECLARATION ,FUNCTION, WHILE, FOREACH, FOR, FUNCTION_DEF, IF, REPEAT,SWITCH};


// struct to match AeroScript Source code types and rows of the raw source code
struct Command{
    AeroScriptType commandType;
    std::string commandString;
};

#endif