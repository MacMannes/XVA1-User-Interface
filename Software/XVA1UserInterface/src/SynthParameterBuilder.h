//
// Created by André Mathlener on 04/04/2021.
//

#ifndef XVA1USERINTERFACE_SYNTHPARAMETERBUILDER_H
#define XVA1USERINTERFACE_SYNTHPARAMETERBUILDER_H


#include "SynthParameter.h"

class SynthParameterBuilder {
    SynthParameter synthParameter;

public:
    explicit SynthParameterBuilder(std::string name) : synthParameter(name) {}

    SynthParameterBuilder &type(ParameterType type);
    SynthParameterBuilder &min(int min);
    SynthParameterBuilder &max(int max);
    SynthParameterBuilder &number(int number);
    SynthParameterBuilder &numbers(std::vector<int>);
    SynthParameterBuilder &bitNumber(int bitNumber);
    SynthParameterBuilder &performanceControlType(int paramNumber1, int paramNumber2);
    SynthParameterBuilder &descriptions(std::vector<std::string>);

    SynthParameter build();
};


#endif //XVA1USERINTERFACE_SYNTHPARAMETERBUILDER_H
