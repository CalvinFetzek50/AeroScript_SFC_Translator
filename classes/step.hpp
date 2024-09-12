/** Step implementation
 *  @file step.hpp */
   
#ifndef STEP_HPP
#define STEP_HPP

#include <map>
#include <string>
#include <any>

template<typename Unit>
class Step{
    private: 

        // string to store the step name
        std::string stepName;

        // int to track the sequence of the step
        int stepSequence;

        // string to store comments related to the step
        std::string stepComment;
        
    public:

        // dictionary to store key: variable name, value: variable value 
        std::map<std::string, std::vector<std::any>> stepVariableMap; 

        // set to store all variable names
        std::set<std::string> namesSet;

        /** method to get the step name 
         * @return step name */
        std::string getName();

        /** method to set the step name 
         * @param name : string of step name */
        void setName(std::string name);

        /** method to get the sequence 
         * @return step sequence */
        int getSequence();

        /** method to set the sequence 
         * @param sequence sequence in the sequencial functional chart  */
        void setSequence(int sequence);

        /** method to get the comment related to the step
         * @return comments (std::string)  */
        std::string getComment();

        /** method to set the comment related to the step
         * @param comment (std::string)  */
        void setComment(std::string comment);

        /** method to update the value of the variables 
         * @param variableName : a string for the target variable
         * @param value : pointer to value associated with the variable name 
         * @return returns true after directly updating the variableMap used as argument. 
         * Returns false, if it cannot update the variable value (if variable does not exist)  */
        bool updateVariable(std::string variableName, std::any value);

        /** method to add variables to the variable map
         * @param variableName : string of the variable name
         * @param value : pointer to value of the variable
         * @param isArray : boolean, true if variable is an array, false if variable is not array
         * @return returns true, if variable has been added. */
        bool addVariable(std::string variableName, std::any value, bool isArray);

        /** method to copy the map containing all variables from another Step class  
         * @param step : step class intance where the map is to be copied over from.
         * @return returns true, if the map has been copied. 
         * Returns false and do nothing if a map already exists in the target. */
        bool copyMap(Step<Unit> step);
        

};

#include "step.tpp"
#endif
