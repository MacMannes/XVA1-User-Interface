//
// Created by André Mathlener on 04/04/2021.
//

#include <vector>
#include "SynthParameterBuilder.h"

SynthParameter SynthParameterBuilder::build() {
    if (synthParameter.type == BITWISE) {
        synthParameter.max = 1;
    }

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

SynthParameterBuilder &SynthParameterBuilder::bitNumber(uint8_t bitNumber) {
    synthParameter.bitNumbers = { bitNumber };
    return *this;
}

SynthParameterBuilder &SynthParameterBuilder::bitNumbers(std::vector<uint8_t> bitNumbers) {
    synthParameter.bitNumbers = bitNumbers;
    return *this;
}

SynthParameterBuilder &SynthParameterBuilder::min(uint8_t min) {
    synthParameter.min = min;
    return *this;
}

SynthParameterBuilder &SynthParameterBuilder::max(uint8_t max) {
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
