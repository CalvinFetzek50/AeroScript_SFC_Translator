/** Transition implementation
 *  @file transition.hpp */


#ifndef TRANSITION_HPP
#define TRANSITION_HPP

#include "step.hpp"


template<typename Unit>
class Transition{
    private:
        // step associated with this transition
        Step<Unit> currentStep;

        // step that comes after this transition
        Step<Unit> nextStep;

        // function name associated with this transition
        std::string functionName;

    public:

        // original and target values to keep track of the transition, updated during transition
        std::string targetVariable;
        std::any targetValue;

        /** Method to set the current Step 
         * @param step an instance of the Step Class */
        void setCurrentStep(Step<Unit> step);

        /** Method to get the current Step 
         * @return returns the current step class. */
        Step<Unit> getCurrentStep();

        /** Method to set the next step
         * @param step an instance of the Step Class */
        void setNextStep(Step<Unit> step);

        /** Method to get the next Step 
         * @return returns the next step class. */
        Step<Unit> getNextStep();

        /** Method to store the function name
         * @param function name of the function in std::string format. */
        void setFunction(std::string function);

        /** Method to get the function name
         * @return returns the function name as a std::string */
        std::string getFunction();






};

#include "transition.tpp"
#endif 