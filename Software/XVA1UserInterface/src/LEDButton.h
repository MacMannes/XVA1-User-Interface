//
// Created by André Mathlener on 24/03/2021.
//

#ifndef XVA1USERINTERFACE_LEDBUTTON_H
#define XVA1USERINTERFACE_LEDBUTTON_H


#include <Adafruit_MCP23017.h>

class LEDButton {
public:
    // Function pointer definition
    typedef void (*onActionFunction)(LEDButton *ledButton, bool released);

    int id = 0;                             // ID for identification

    LEDButton(Adafruit_MCP23017 *mcp, uint8_t buttonPin, uint8_t ledPin, int id, onActionFunction actionFunc);

    void begin();

    void process(int pinState);

    void setLED(bool on);


private:
    Adafruit_MCP23017 *mcp = nullptr;      // Pointer the I2C GPIO expander it's connected to
    uint8_t ledPin = 0;
    uint8_t buttonPin = 0;
    onActionFunction actionFunc = nullptr; // Function pointer, will be called when there is an action happening

    int currentState;
    int lastButtonState;

    unsigned long lastDebounceTime = 0;     // The last time the output pin was toggled
    unsigned long debounceDelay = 10;       // The debounce time
};



#endif //XVA1USERINTERFACE_LEDBUTTON_H
