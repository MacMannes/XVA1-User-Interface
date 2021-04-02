//
// Created by André Mathlener on 02/04/2021.
//

#include "LEDButton.h"

LEDButton::LEDButton(Adafruit_MCP23017 *mcp, uint8_t buttonPin, uint8_t ledPin, int id, onActionFunction actionFunc)
        : Button(mcp, buttonPin, id, actionFunc) {
    this->ledPin = ledPin;
}

void LEDButton::begin() {
    Button::begin();

    mcp->pinMode(ledPin, OUTPUT);
    mcp->digitalWrite(ledPin, LOW);
}

void LEDButton::setLED(bool onOrOff) {
    ledState = onOrOff;
    mcp->digitalWrite(ledPin, onOrOff ? HIGH : LOW);
}

bool LEDButton::getLED() const {
    return ledState;
}

void LEDButton::toggleLED() {
    ledState = !ledState;
    mcp->digitalWrite(ledPin, ledState ? HIGH : LOW);
}
