#include <Arduino.h>

#include <TFT_eSPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>

#include "SynthParameter.h"
#include "Button.h"
#include "LEDButton.h"
#include "SynthParameterBuilder.h"
#include "XVA1SynthParameters.h"
#include "Hardware.h"
#include "main.h"

unsigned long lastTransition;
unsigned long revolutionTime = 0;

int activeShortcut = 0;

bool shiftButtonPushed = false;
bool mainRotaryButtonPushed = false;

void setup() {
    SerialUSB.begin(115200);

    //while the serial stream is not open, do nothing:
//     while (!SerialUSB);

    SerialUSB.println("\n");
    SerialUSB.println("===================");
    SerialUSB.println("XVA1 User Interface");
    SerialUSB.println("===================\n");

    SerialUSB.println("Initializing MCP23017 #1");
    mcp1.begin(0);
    SerialUSB.println("Initializing MCP23017 #2");
    mcp2.begin(1);
    SerialUSB.println("Initializing MCP23017 #3");
    mcp3.begin(2);
    SerialUSB.println("Initializing MCP23017 #1-3 done");
    
    // Initialize input encoders (pin mode, interrupt)
    for (auto &rotaryEncoder : rotaryEncoders) {
        rotaryEncoder.init();
    }

    SerialUSB.println("Initializing OLED displays");
    initOLEDDisplays();
    SerialUSB.println("Initializing Buttons");
    initButtons();

    Serial1.begin(500000); // XVA1 Serial

    tft.init();
    tft.setRotation(0);  // 0 & 2 Portrait. 1 & 3 landscapeooooooo;;
    tft.fillScreen(TFT_BLACK);

    tft.setCursor(0, 0, 1);
    // Set the font colour to be white with a black background, set text size multiplier to 1

    tft.setTextColor(MY_ORANGE, TFT_BLACK);
    tft.setTextSize(2);
    tft.println("XVA1 Synthesizer");

    synthesizer.selectPatch(1);
    displayPatchInfo();

    mainRotaryEncoder.begin(true);
}


void loop() {
    unsigned char result = mainRotaryEncoder.process();
    if (result) {
        handleMainEncoder(result == DIR_CW);
    }

    readButtons();
    pollAllMCPs();
}

void rotaryEncoderChanged(bool clockwise, int id) {
    unsigned long now = millis();
    revolutionTime = now - lastTransition;

    int speed = 1;
    if (revolutionTime < 50) {
        speed = 20;
    } else if (revolutionTime < 125) {
        speed = 10;
    } else if (revolutionTime < 250) {
        speed = 2;
    }

    lastTransition = now;

    Serial.println("Encoder " + String(id) + ": "
                   + (clockwise ? String("clockwise") : String("counter-clock-wise")) + ", Speed: " + String(speed));

    switch (id) {
        case 1:
            handleParameterChange(&param1, clockwise, speed);
            displayTwinParameters(&param1, &param2, 0);
            break;
        case 2:
            handleParameterChange(&param2, clockwise, speed);
            displayTwinParameters(&param1, &param2, 0);
            break;
        case 3:
            handleParameterChange(&param3, clockwise, speed);
            displayTwinParameters(&param3, &param4, 1);
            break;
        case 4:
            handleParameterChange(&param4, clockwise, speed);
            displayTwinParameters(&param3, &param4, 1);
            break;
    }
}

void initOLEDDisplays() {
    for (int d = 0; d < 4; d++) {
        multiplexer.selectChannel(d);
        // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
        display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

        display.clearDisplay();
        display.display();
    }
}

void initButtons() {
    for (auto &button : allButtons) {
        button->begin();
    }

    pinMode(3, INPUT_PULLUP);
}

void readButtons() {
    bool mainRotaryButtonState = (digitalRead(3) == LOW);
    if (mainRotaryButtonState != mainRotaryButtonPushed) {
        mainRotaryButtonPushed = mainRotaryButtonState;
        mainRotaryButtonChanged(!mainRotaryButtonPushed);
    }
}

void handleMainEncoder(bool clockwise) {
    int currentPatchNumber = synthesizer.getPatchNumber();
    int oldValue = currentPatchNumber;

    if (clockwise) {
        if (currentPatchNumber < 128) {
            currentPatchNumber++;
        }
    } else {
        if (currentPatchNumber > 1) {
            currentPatchNumber--;
        }
    }

    SerialUSB.print("Selecting patch: ");
    SerialUSB.println(currentPatchNumber);

    if (currentPatchNumber != oldValue) {
        synthesizer.selectPatch(currentPatchNumber);
        displayPatchInfo();
    }
}

void displayPatchInfo() {
    int currentPatchNumber = synthesizer.getPatchNumber();

//  tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString("Patch", 0, 40, 1);

    tft.setTextColor(MY_ORANGE, TFT_BLACK);

    // Set the padding to the maximum width that the digits could occupy in font 4
    // This ensures small numbers obliterate large ones on the screen
    tft.setTextPadding(tft.textWidth("999", 4));
    // Draw the patch number in font 4
    tft.drawNumber(currentPatchNumber, 0, 65, 4);

    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.setTextPadding(tft.textWidth("XXXXXXXXXXXXXXXXXXXXXXXXX", 1));
    // Draw the patch name in font 1
    tft.drawString(synthesizer.getPatchName().c_str(), 0, 120, 1);

    // Reset text padding to 0 otherwise all future rendered strings will use it!
    tft.setTextPadding(0);

    displayTwinParameters(&param1, &param2, 0);
    displayTwinParameters(&param3, &param4, 1);

}

void drawCenteredText(const char *buf, int x, int y) {
    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds(buf, x, y, &x1, &y1, &w, &h); //calc width of new string
    display.setCursor(x - w / 2, y);
    display.print(buf);
}

void printHex(uint8_t num) {
    char hexCar[3];

    sprintf(hexCar, "%02X", num);
    SerialUSB.print(hexCar);
}

void pollAllMCPs() {
    // Read all MCPs and feed the input to each encoder and shortcut button.
    // This is more efficient than reading one pin state at a time
    for (auto &mcp : allMCPs) {
        uint16_t gpioAB = mcp->readGPIOAB();

        for (auto &rotaryEncoder : rotaryEncoders) {
            // Only feed this in the encoder if this is coming from the correct MCP
            if (rotaryEncoder.getMCP() == mcp) {
                rotaryEncoder.feedInput(gpioAB);
            }
        }

        for (auto &button : allButtons) {
            if (button->getMcp() == mcp) {
                button->feedInput(gpioAB);
            }
        }
    }
}

void displayTwinParameters(SynthParameter *parameter1, SynthParameter *parameter2, int displayNumber) {
    int byte1;
    int byte2;

    if (parameter1->getType() == PERFORMANCE_CTRL) {
        byte msb = synthesizer.getParameter(parameter1->getNumber(0));
        byte lsb = synthesizer.getParameter(parameter1->getNumber(1));
        int combined = (msb << 7) + lsb;

        byte1 = (int) combined;
    } else {
        byte1 = (int) synthesizer.getParameter(parameter1->getNumber());
    }

    if (parameter2->getType() == PERFORMANCE_CTRL) {
        byte msb = synthesizer.getParameter(parameter2->getNumber(0));
        byte lsb = synthesizer.getParameter(parameter2->getNumber(1));
        int combined = (msb << 7) + lsb;

        byte2 = (int) combined;
    } else {
        byte2 = (int) synthesizer.getParameter(parameter2->getNumber());
    }

    char printValue1[20];
    if (byte1 < parameter1->getDescriptions().size()) {
        strcpy(printValue1, parameter1->getDescriptions()[byte1].c_str());
    } else {
        sprintf(printValue1, "%d", byte1);
    }
    char printValue2[20];
    if (byte2 < parameter2->getDescriptions().size()) {
        strcpy(printValue2, parameter2->getDescriptions()[byte2].c_str());
    } else {
        sprintf(printValue2, "%d", byte2);
    }


    displayTwinParameters(parameter1->getName().c_str(), printValue1, parameter2->getName().c_str(), printValue2, displayNumber);
}

void displayTwinParameters(const char *title1, char *value1, const char *title2, char *value2, int displayNumber) {
    multiplexer.selectChannel(displayNumber);

    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(WHITE);
    drawCenteredText(title1, 64, 0);

    display.setTextSize(2);
    drawCenteredText(value1, 64, 12);

    display.drawLine(0, 30, display.width() - 1, 30, WHITE);


    display.setTextSize(1);
    drawCenteredText(title2, 64, 34);

    display.setTextSize(2);
    drawCenteredText(value2, 64, 47);

    display.display();
}

void handleParameterChange(SynthParameter *param, bool clockwise, int speed) {
    int currentValue;

    if (param->getType() == PERFORMANCE_CTRL) {
        byte msb = synthesizer.getParameter(param->getNumber(0));
        byte lsb = synthesizer.getParameter(param->getNumber(1));
        int combined = (msb << 7) + lsb;
        currentValue = combined;
    } else {
        currentValue = synthesizer.getParameter(param->getNumber());
    }
    int newValue = -1;

    if (clockwise) {
        if (currentValue < param->getMax()) {
            newValue = currentValue + speed;
            if (newValue > param->getMax()) {
                newValue = param->getMax();
            }
        }
    } else {
        if (currentValue > param->getMin()) {
            newValue = currentValue - speed;
            if (newValue < param->getMin()) {
                newValue = param->getMin();
            }
        }
    }


    if (newValue >= 0 && newValue != currentValue) {
        SerialUSB.print("New value: ");
        SerialUSB.println(newValue);
        if (param->getType() == PERFORMANCE_CTRL) {
            int msb = newValue >> 7;
            int lsb = newValue & 127;

            synthesizer.setParameter(param->getNumber(0), msb);
            synthesizer.setParameter(param->getNumber(1), lsb);
        } else {
            synthesizer.setParameter(param->getNumber(), newValue);
        }
    }

}

void shortcutButtonChanged(Button *btn, bool released) {
    SerialUSB.print("Shortcut-button #");
    SerialUSB.print(btn->id);
    SerialUSB.print(" ");
    SerialUSB.println((released) ? "RELEASED" : "PRESSED");

    activeShortcut = (shiftButtonPushed && btn->id <= 4) ? btn->id + 8 : btn->id;

    if (!released) {
        SerialUSB.print("Active Shortcut: ");
        SerialUSB.println(activeShortcut);
        for (auto &shortcutButton : shortcutButtons) {
            shortcutButton->setLED(shortcutButton->id == btn->id);
        }

        //TODO: Remove temporary debug information
        if (activeShortcut == 5) {
            parameterController.setSection(&oscillatorSection);
        } else {
            parameterController.setSection(nullptr);
        }
    }
}

void mainButtonChanged(Button *btn, bool released) {
    SerialUSB.print("Main-button #");
    SerialUSB.print(btn->id);
    SerialUSB.print(" ");
    SerialUSB.println((released) ? "RELEASED" : "PRESSED");

    switch (btn->id) {
        case SHIFT_BUTTON:
            shiftButtonPushed = !released;
            break;
        case ESC_BUTTON:
            if (activeShortcut > 0) {
                activeShortcut = 0;
                for (auto &shortcutButton : shortcutButtons) {
                    shortcutButton->setLED(false);
                }
            }
            parameterController.setSection(nullptr);
    }
}

void rotaryButtonChanged(Button *btn, bool released) {
    SerialUSB.print("Rotary-button #");
    SerialUSB.print(btn->id);
    SerialUSB.print(" ");
    SerialUSB.println((released) ? "RELEASED" : "PRESSED");
}

void upOrDownButtonChanged(Button *btn, bool released) {
    SerialUSB.print((btn->id == UP_BUTTON) ? "Up" : "Down");
    SerialUSB.print("-button");
    SerialUSB.print(" ");
    SerialUSB.println((released) ? "RELEASED" : "PRESSED");

    if (!released) {
        if (btn->id == UP_BUTTON) {
            parameterController.upButtonTapped();
        } else {
            parameterController.downButtonTapped();
        }
    }
}

void mainRotaryButtonChanged(bool released) {
    SerialUSB.print("MAIN-Rotary-button ");
    SerialUSB.println((released) ? "RELEASED" : "PRESSED");

}
