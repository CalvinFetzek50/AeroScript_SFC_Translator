#ifndef MATCH_FUNCTIONS_HPP
#define MATCH_FUNCTIONS_HPP

#include "match_functions.tpp"

/** function to determine the Aeroscript function imported into the function Class.
 * It will update the targetVariable and targetValue of the transition Class.
 * @param functionStr the string containing the AeroScript function name
 * @param transition the transition class used to update the targetVariable and targetValue */
template <typename Unit>
void findAeroScriptFunction(const std::string functionStr, Transition<Unit>& transition);

/**  Helper function to find the nth occurrence of hte character in a string */
int nthOccurrence(const std::string& str, const std::string& findMe, int nth);

#endif