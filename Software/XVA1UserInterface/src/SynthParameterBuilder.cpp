//
// Created by André Mathlener on 04/04/2021.
//

#include <vector>
#include "SynthParameterBuilder.h"

SynthParameter SynthParameterBuilder::build() {
    return std::move(synthParameter);
}

SynthParameterBuilder &SynthParameterBuilder::type(ParameterType type) {
    synthParameter.type = type;
    return *this;
}

SynthParameterBuilder &SynthParameterBuilder::number(int number) {
    synthParameter.numbers = { number };
    return *this;
}

SynthParameterBuilder &SynthParameterBuilder::numbers(std::vector<int> numbers) {
    synthParameter.numbers = numbers;
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

SynthParameterBuilder &SynthParameterBuilder::descriptions(std::vector<std::string> descriptions) {
    synthParameter.descriptions = descriptions;
    return *this;
}

SynthParameterBuilder &SynthParameterBuilder::performanceControlType(int paramNumber1, int paramNumber2) {
    synthParameter.type = PERFORMANCE_CTRL;
    synthParameter.numbers = { paramNumber1, paramNumber2 };
    return *this;
}
