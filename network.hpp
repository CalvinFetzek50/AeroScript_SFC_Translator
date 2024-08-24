/* File to implement the network of nodes */

#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "step.hpp"
#include "transition.hpp"
#include <vector>

template<typename Unit>
struct Node{
    
    int sequence;
    Step<Unit> step;
    Transition<Unit> transition;

};

template<typename Unit>
class Network{
    private:

        // vector to store all nodes in the source file
        std::vector<Node<Unit>> nodeVector;

    public:

        /** Method to add a node to the network
         * @param node : A combination of a step and transition that will be added to the network
         * @return : returns true if the node is successfully added, if the node does not contain either
         * a step or transition, then returns false and will not add the node to the vector */
        bool addNode(Node<Unit> node);

        /** Method to remove a node from the network
         * @param index : a int specifying the sequence of the node that will be removed.
         * @return : returns true if hte node is successfully removed. If the index is out of range, return false
         * and do nothing. */
        bool removeNode(int index);

        /** Method to get the node from a index in the  vector 
         * @param index : a int specifying the node to be retrieved
         * @throw if index is out of range it will through an out of range error.
         * @return node : Node class with the specified sequence. */
        Node<Unit> getNode(int index);

        /** method to return the size of the nodeVector
         * @return size of the nodevector in integer */
        int getSize();

};



#include "network.tpp"

#endif