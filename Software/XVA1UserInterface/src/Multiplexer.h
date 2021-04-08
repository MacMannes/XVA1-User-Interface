//
// Created by André Mathlener on 08/04/2021.
//

#ifndef XVA1USERINTERFACE_MULTIPLEXER_H
#define XVA1USERINTERFACE_MULTIPLEXER_H


#include <cstdint>

class Multiplexer {
private:
    uint8_t address;

public:
    Multiplexer(uint8_t address);

    void selectChannel(uint8_t i2c_bus);
};


#endif //XVA1USERINTERFACE_MULTIPLEXER_H
