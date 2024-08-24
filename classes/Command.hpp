#ifndef COMMAND_CPP
#define COMMAND_CPP

#include <string>

// Enumerator representing AeroScript Source code types
enum AeroScriptType {VAR, IF, COMMENT, DECLARATION ,FUNCTION};


// struct to match AeroScript Source code types and rows of the raw source code
struct Command{
    AeroScriptType commandType;
    std::string commandString;
};

#endif