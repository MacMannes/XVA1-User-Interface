//
// Created by André Mathlener on 02/04/2021.
//

#ifndef XVA1USERINTERFACE_LEDBUTTON_H
#define XVA1USERINTERFACE_LEDBUTTON_H


#include "Button.h"

class LEDButton: public Button {
public:
    LEDButton(Adafruit_MCP23017 *mcp, uint8_t buttonPin, uint8_t ledPin, int id, onActionFunction actionFunc);

    void setLED(bool on);

    bool getLED() const;

    void toggleLED();

    void begin() override;

private:
    uint8_t ledPin = 0;
    bool ledState;
};


#endif //XVA1USERINTERFACE_LEDBUTTON_H
