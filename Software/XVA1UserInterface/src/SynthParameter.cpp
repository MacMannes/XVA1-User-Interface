//
// Created by André Mathlener on 04/04/2021.
//

#include "SynthParameter.h"

SynthParameter::SynthParameter(std::string name) {
    this->name = name;
}

ParameterType SynthParameter::getType() const {
    return type;
}

const std::string &SynthParameter::getName() const {
    return name;
}

int SynthParameter::getNumber() const {
    return number;
}

int SynthParameter::getNumber2() const {
    return number2;
}

int SynthParameter::getMin() const {
    return min;
}

int SynthParameter::getMax() const {
    return max;
}

const std::vector<std::string> &SynthParameter::getDescriptions() const {
    return descriptions;
}


