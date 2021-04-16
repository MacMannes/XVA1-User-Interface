//
// Created by André Mathlener on 04/04/2021.
//

#ifndef XVA1USERINTERFACE_SYNTHPARAMETER_H
#define XVA1USERINTERFACE_SYNTHPARAMETER_H


#include <string>
#include <utility>
#include <vector>
#include "ParameterType.h"

class SynthParameter {
    ParameterType type = NUMERIC;
    std::string name;
    // This will contain one or more parameter numbers (4 for XVA1 oscillators, 8 for XFM2 operators, 2 for Performance controls),
    std::vector<int> numbers;
    std::vector<uint8_t> bitNumbers;
    uint8_t min = 0;
    uint8_t max = 255;
    std::vector<std::string> descriptions;

public:
    explicit SynthParameter(std::string name);

    friend class SynthParameterBuilder;

    ParameterType getType() const;

    const std::string &getName() const;

    int getNumber() const;

    int getNumber(int index) const;

    uint8_t getBitNumber() const;

    uint8_t getBitNumber(int index) const;

    uint8_t getMin() const;

    uint8_t getMax() const;

    const std::vector<std::string> &getDescriptions() const;
};


#endif //XVA1USERINTERFACE_SYNTHPARAMETER_H
