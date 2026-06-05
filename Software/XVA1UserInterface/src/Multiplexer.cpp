//
// Created by André Mathlener on 08/04/2021.
//

#include "Multiplexer.h"

#include <Wire.h>

void Multiplexer::selectChannel(uint8_t i2c_bus) {
    if (i2c_bus > 7) return;
    Wire.beginTransmission(address);
    Wire.write(1 << i2c_bus);
    Wire.endTransmission();
}

Multiplexer::Multiplexer(uint8_t address) : address(address) {
}
