#include <iostream>
#include <fstream>
#include <string> 
#include <vector>

#include "textReader.hpp"



int main(){

    // read in the test file as string to inputString
    std::string inputString;
    std::ifstream sourceFile ("../Cycle_Motion_Example.txt");
    char c;

    if (sourceFile.is_open()){
        while (!sourceFile.eof()){
            sourceFile.get(c);
            inputString.push_back(c);
        }
        sourceFile.close();
    }else{
        std::cout << "Unable to open the input file";
        return -1;
    }

    return 0;
}