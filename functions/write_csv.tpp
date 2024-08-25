
#include <string>
#include "../classes/network.hpp"

/** function to write the network onto a csv file
 * @param filename filename of the output file as std::string
 * @param network Network class that contains the information of the AeroScript Source Code */
template <typename Unit>
void write_csv(std::string filename, Network<Unit> network){
    
    // Create an output filestream object
    std::ofstream myFile(filename);

    myFile << "start" << "\n";
    myFile << "|";
    myFile << "\n";
    
    // Send data to the stream
    for(int i = 0; i < network.getSize(); ++i){

        Node<Unit> currentNode = network.getNode(i); 

        // add step name
        myFile << "Step_" + std::to_string(currentNode.sequence);
        myFile << ",,";

        // add comments
        myFile << "N,";
        //myFile << currentNode.step.getComment();
        //myFile << "\n";

        // add functions
        // add double quotes into the beginning and end of string to ouput into csv file
        myFile << "\"" + currentNode.transition.getFunction() + "\"";
        myFile << "\n";
        
        // add transtions
        myFile << "|" << ",";
        myFile << currentNode.transition.targetVariable + " = " + currentNode.transition.targetValue;
        myFile << "\n";

    }

    myFile << "end";
    
    // Close the file
    myFile.close();
}