#ifndef COMBINE_TEXT_HPP
#define COMBINE_TEXT_HPP

#include "combine_text.tpp"

/** function to combine for loops into one group
 * @param commandVector : a vector containing Command structs. This is the output of the rowIdentifier function
 * @param step : the initialized step class which contains all the variables used in the script.
 */
template <typename Unit>
void combineForLoops(std::vector<Command>& commandVector, Step<Unit>& step);

#endif 