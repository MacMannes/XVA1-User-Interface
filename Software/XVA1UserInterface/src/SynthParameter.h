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
    // or a parameter number and a bit-number in case of a bitwise parameter
    std::vector<int> numbers;
    int min = 0;
    int max = 255;
    std::vector<std::string> descriptions;

public:
    explicit SynthParameter(std::string name);

    friend class SynthParameterBuilder;

    ParameterType getType() const;

    const std::string &getName() const;

    int getNumber() const;

    int getNumber2() const;

    int getNumber(int index);

    int getMin() const;

    int getMax() const;

    const std::vector<std::string> &getDescriptions() const;
};


#endif //XVA1USERINTERFACE_SYNTHPARAMETER_H
