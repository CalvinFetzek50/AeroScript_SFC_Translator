#include "network.hpp"
#include <exception>

template<typename Unit> 
bool Network<Unit>::addNode(Node<Unit> node){
    
    nodeVector.push_back(node);
    return true;
    
}

template<typename Unit>
bool Network<Unit>::removeNode(int index){

    if ((index > nodeVector.size()) || (index < 0)){
        /* debug */
        std::cout << "Index is out of range. " << std::endl;
        /* debug */
        return false;
    }else{
        nodeVector.erase(nodeVector.begin()+index);
        return true;
    }
}

template<typename Unit>
Node<Unit> Network<Unit>::getNode(int index){

    if ((index > nodeVector.size()) || (index < 0)){
        
        throw std::out_of_range("Index is out of range of the node vector.");
    }else{
        
        return nodeVector.at(index);
    
    }
}

template<typename Unit>
int Network<Unit>::getSize(){
    return nodeVector.size();
}