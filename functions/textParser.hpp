#ifndef TEXTPARSER_CPP
#define TEXTPARSER_CPP

#include "textParser.tpp"

/** This function parses the AeroScript Source code into blocks of strings based on rows.
 * @param sourceScript : AeroScript source code stored as a single string
 * @return Returns the vector with source code parsed by line and tabs removed */
std::vector<std::string> rowParser(std::string sourceScript);


/** This function combines the comments in the vector of Command structs
 * @param commandVector : vector containing command structs. This is the output of the rowIdentifier function. */
void combineComments(std::vector<Command>& commandVector);

/** this function cassifies the parsed lines into the different types: 
 * variables, comments, conditionals and loops, etc.
 * @pre run rowParser(sourceScript) before running this function.
 * @param rowVector : AeroScript source code stored as a vector of strings corresponding to each row.
 * @return returns a vector of AeroScript constructs. */
std::vector<Command> rowIdentifier(std::vector<std::string> rowVector);

#endif 