#ifndef INITIALIZATION_HPP
#define INITIALIZATION_HPP


#include "variable_init.tpp"

/** This function finds all variables names in the script and adds them to the variable map in the Step class
 * @param commandVector : a vector containing Command structs. This is the output of the rowIdentifier function
 * @param step : the initialized step class which contains all the variables used in the script. */
template <typename Unit>
void findVariables(std::vector<Command>& commandVector, Step<Unit>& step);

/**  This function initializes all variables in the variable map
 * @param commandVector : a vector containing Command structs. Output after findVariables function.
 * @param step : the initialized step class which contains all the variables used in the script.*/
template <typename Unit>
void initializeVariables(std::vector<Command>& commandVector, Step<Unit>& step);

#endif 