//
// Created by André Mathlener on 04/04/2021.
//

#include "SynthParameter.h"

SynthParameter::SynthParameter(std::string name) {
    this->_name = name;
}

ParameterType SynthParameter::getType() const {
    return _type;
}

const std::string &SynthParameter::getName() const {
    return _name;
}

int SynthParameter::getNumber() const {
    return _numbers[0];
}

uint8_t SynthParameter::getBitNumber() const {
    return _bitNumbers[0];
}

uint8_t SynthParameter::getBitNumber(int index) const {
    if (index < _bitNumbers.size()) {
        return _bitNumbers[index];
    }

    return _bitNumbers[0];
}

int SynthParameter::getNumber(int index) const {
    if (index < _numbers.size()) {
        return _numbers[index];
    }

    return _numbers[0];
}

uint8_t SynthParameter::getMin() const {
    return _min;
}

uint8_t SynthParameter::getMax() const {
    return _max;
}

const std::vector<std::string> &SynthParameter::getDescriptions() const {
    return _descriptions;
}

SynthParameter &SynthParameter::type(ParameterType type) {
    _type = type;
    return *this;
}

SynthParameter &SynthParameter::min(int min) {
    _min = min;
    return *this;
}

SynthParameter &SynthParameter::max(int max) {
    _max = max;
    return *this;
}

SynthParameter &SynthParameter::number(int number) {
    _numbers.push_back(number);
    return *this;
}

SynthParameter &SynthParameter::numbers(std::initializer_list<int> numbers) {
    for (const auto &item : numbers) {
        _numbers.push_back(item);
    }
    return *this;
}

SynthParameter &SynthParameter::bitNumber(int bitNumber) {
    _bitNumbers.push_back(bitNumber);
    return *this;
}

SynthParameter &SynthParameter::bitNumbers(std::initializer_list<int> bitNumbers) {
    for (const auto &item : bitNumbers) {
        _bitNumbers.push_back(item);
    }
    return *this;
}

SynthParameter &SynthParameter::descriptions(std::initializer_list<std::string> descriptions) {
    for (const auto &item : descriptions) {
        _descriptions.push_back(item);
    }
    return *this;
}

SynthParameter &SynthParameter::performanceControlType(int paramNumber1, int paramNumber2) {
    _type = PERFORMANCE_CTRL;
    _numbers.push_back(paramNumber1);
    _numbers.push_back(paramNumber2);
    return *this;
}



