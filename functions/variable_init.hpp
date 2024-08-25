#ifndef INITIALIZATION_HPP
#define INITIALIZATION_HPP


#include "variable_init.tpp"

/** This function initializes the variable map in the Step class
 * @param commandVector : a vector containing Command structs. This is the output of the rowIdentifier function
 * @param step : the initialized step class which contains all the variables used in the script.
 * @return returns true, if all variables have been added to the Step class, else returns false. */
template <typename Unit>
bool initializeVariables(std::vector<Command>& commandVector, Step<Unit>& step);

#endif 