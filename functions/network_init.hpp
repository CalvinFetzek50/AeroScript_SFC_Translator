#ifndef NETWORK_INIT_HPP
#define NETWORK_INIT_HPP

#include "network_init.tpp"

/** function to iterate through each line of AeroScript Source code and create a network of Nodes consisting of both Step and Transition
 * @param commandVector std::vector of type Command. This vector is modified after running initializeVariables().
 * @param init_step Step<Unit> class with the variable map filled in. This class is modified after running initializeVariables().
 * @param network Network class to store all steps and transitions
 * @return returns true if all lines were processed and network is completed. False if not. */
template <typename Unit>
bool createNetwork(std::vector<Command>& commandVector, Step<Unit>& init_step, Network<Unit>& network);

#endif 