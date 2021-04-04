//
// Created by André Mathlener on 04/04/2021.
//

#ifndef XVA1USERINTERFACE_SYNTHPARAMETER_H
#define XVA1USERINTERFACE_SYNTHPARAMETER_H


#include <string>
#include <utility>
#include "ParameterType.h"

class SynthParameter {
    ParameterType type = NUMERIC;
    std::string name;
    int number = -1;
    int number2 = -1;
    int min = 0;
    int max = 255;
    char *descriptions[25] = {};

public:
    explicit SynthParameter(std::string name);

    friend class SynthParameterBuilder;

    ParameterType getType() const;

    const std::string &getName() const;

    int getNumber() const;

    int getNumber2() const;

    int getMin() const;

    int getMax() const;

    char *const *getDescriptions() ;
};


#endif //XVA1USERINTERFACE_SYNTHPARAMETER_H
