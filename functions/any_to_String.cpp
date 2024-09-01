

#include <typeinfo>
#include <string>
#include <any>


/** Method to get a string for the target value 
 * @return returns the value in std::string format */
std::string any_to_string(std::any targetValue){

    if (targetValue.type().name() == typeid(int).name()){
        // if the variable value is an integer
        int value = std::any_cast<int>(targetValue);
        return std::to_string(value);

    }else if (targetValue.type().name() == typeid(double).name()){
        // if the variable value is an double 
        double value = std::any_cast<double>(targetValue);
        return std::to_string(value);
    
    }else if (targetValue.type().name() == typeid(std::string).name()){
        // if the variable value is a string
        std::string value =  std::any_cast<std::string>(targetValue);
        return value;
        
    }else if (targetValue.type().name() == typeid(char).name()){
        // if the variable value is a char
        char valueChar = std::any_cast<char>(targetValue);
        std::string value(1,valueChar);
        return value;
    }else{
        // if it is another type
        return "type not int / double / string";
    }
}
