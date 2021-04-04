//
// Created by André Mathlener on 04/04/2021.
//

#include "SynthParameterBuilder.h"

SynthParameter SynthParameterBuilder::build() {
    return std::move(synthParameter);
}

SynthParameterBuilder &SynthParameterBuilder::type(ParameterType type) {
    synthParameter.type = type;
    return *this;
}

SynthParameterBuilder &SynthParameterBuilder::number(int number) {
    synthParameter.number = number;
    return *this;
}

SynthParameterBuilder &SynthParameterBuilder::number2(int number2) {
    synthParameter.number2 = number2;
    return *this;
}

SynthParameterBuilder &SynthParameterBuilder::min(int min) {
    synthParameter.min = min;
    return *this;
}

SynthParameterBuilder &SynthParameterBuilder::max(int max) {
    synthParameter.max = max;
    return *this;
}

SynthParameterBuilder &SynthParameterBuilder::performanceControlType(int paramNumber1, int paramNumber2) {
    synthParameter.type = PERFORMANCE_CTRL;
    synthParameter.number = paramNumber1;
    synthParameter.number2 = paramNumber2;
    return *this;
}
