#include "transition.hpp"

template<typename Unit>
void Transition<Unit>::setCurrentStep(Step<Unit> step){
    currentStep = step;
}

template<typename Unit>
Step<Unit> Transition<Unit>::getCurrentStep(){
    return currentStep;
}

template<typename Unit>
void Transition<Unit>::setNextStep(Step<Unit> step){
    nextStep = step;
}

template<typename Unit>
Step<Unit> Transition<Unit>::getNextStep(){
    return nextStep;
}


template<typename Unit>
void Transition<Unit>::setFunction(std::string function){
    functionName = function;
}

template<typename Unit>
std::string Transition<Unit>::getFunction(){
    return functionName;
}
