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
    SynthParameterBuilder &min(uint8_t min);
    SynthParameterBuilder &max(uint8_t max);
    SynthParameterBuilder &number(int number);
    SynthParameterBuilder &numbers(std::vector<int>);
    SynthParameterBuilder &bitNumber(uint8_t bitNumber);
    SynthParameterBuilder &bitNumbers(std::vector<uint8_t>);
    SynthParameterBuilder &performanceControlType(int paramNumber1, int paramNumber2);
    SynthParameterBuilder &descriptions(std::vector<std::string>);

    SynthParameter build();
};


#endif //XVA1USERINTERFACE_SYNTHPARAMETERBUILDER_H
