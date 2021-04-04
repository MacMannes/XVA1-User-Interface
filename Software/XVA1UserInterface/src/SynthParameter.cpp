//
// Created by André Mathlener on 04/04/2021.
//

#include "SynthParameter.h"

SynthParameter::SynthParameter(std::string name) {
    this->type = NUMERIC;
    this->min = 0;
    this->max = 255;
    this->number = -1;
    this->number = -2;
    this->name = name;
}

char *const *SynthParameter::getDescriptions() {
    return descriptions;
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

