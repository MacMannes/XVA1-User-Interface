#include <Arduino.h>

#include <TFT_eSPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>

#include "SynthParameter.h"
#include "Button.h"
#include "Hardware.h"
#include "Globals.h"
#include "FreeMemory.h"

unsigned long lastTransition;
unsigned long revolutionTime = 0;

int activeShortcut = 0;

bool shiftButtonPushed = false;
bool mainRotaryButtonPushed = false;

/* function prototypes */

void handleMainEncoder(bool clockwise);

void initOLEDDisplays();

void pollAllMCPs();

void readButtons();

void displayPatchInfo();

void displayPatchInfo(bool paintItBlack);

void initButtons();

void clearShortcut();

void clearMainScreen();

void initMainScreen();

void initRotaryEncoders();

void rtrim(std::string &s, char c);

void setup() {
    Serial.begin(115200);

    //while the serial stream is not open, do nothing:
//    while (!Serial);

    Serial.println("\n");
    Serial.println("===================");
    Serial.println("XVA1 User Interface");
    Serial.println("===================\n");

    mcp1.begin(0);
    mcp2.begin(1);
    mcp3.begin(2);

    synthesizer.begin();

    initMainScreen();
    clearMainScreen();

    initRotaryEncoders();
    initOLEDDisplays();
    initButtons();

    synthesizer.selectPatch(4);
    parameterController.setDefaultSection();
    displayPatchInfo();

    mainRotaryEncoder.begin(true);

    Serial.print("freeMemory()=");
    Serial.println(freeMemory());
}

void loop() {
    unsigned char result = mainRotaryEncoder.process();
    if (result) {
        bool clockwise = result == DIR_CW;
        if (activeShortcut != 0) {
            bool consumed = parameterController.rotaryEncoderChanged(0, clockwise, 1);
            if (!consumed) {
                handleMainEncoder(clockwise);
            }
        } else {
            handleMainEncoder(clockwise);
        }
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

    parameterController.rotaryEncoderChanged(id, clockwise, speed);
}

void initRotaryEncoders() {
    for (auto &rotaryEncoder : rotaryEncoders) {
        rotaryEncoder.init();
    }
}

void initMainScreen() {
    tft.init();
    tft.setRotation(0);  // 0 & 2 Portrait. 1 & 3 landscape;
}

void initOLEDDisplays() {
    for (int d = 0; d < 4; d++) {
        multiplexer.selectChannel(d);
        // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
        display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

        display.setTextWrap(false);
        display.clearDisplay();
        display.display();
    }
}

void initButtons() {
    for (auto &button : allButtons) {
        button->begin();
    }

    pinMode(MAIN_ROTARY_BTN_PIN, INPUT_PULLUP);
}

void readButtons() {
    bool mainRotaryButtonState = (digitalRead(MAIN_ROTARY_BTN_PIN) == LOW);
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

    Serial.print("Selecting patch: ");
    Serial.println(currentPatchNumber);

    if (currentPatchNumber != oldValue) {
        synthesizer.selectPatch(currentPatchNumber);
        clearShortcut();
        parameterController.setDefaultSection();
        displayPatchInfo();
    }
}

void displayPatchInfo() {
    displayPatchInfo(false);
}

void rtrim(std::string &s, char c) {

    if (s.empty())
        return;

    std::string::iterator p;
    for (p = s.end(); p != s.begin() && *--p == c;);

    if (*p != c)
        p++;

    s.erase(p, s.end());
}

void displayPatchInfo(bool paintItBlack) {
    int currentPatchNumber = synthesizer.getPatchNumber();

    tft.setTextColor(paintItBlack ? MY_ORANGE : TFT_BLACK);

    tft.setTextSize(2);
    tft.setTextDatum(1);
    tft.drawString("XVA1 Synthesizer", 119, 4, 1);

    tft.setTextColor((paintItBlack) ? TFT_BLACK : TFT_GREY);
    tft.drawString("Patch", 119, 40, 1);

    if (!paintItBlack) {
        tft.setTextColor(MY_ORANGE, TFT_BLACK);
    }

    // Set the padding to the maximum width that the digits could occupy in font 4
    // This ensures small numbers obliterate large ones on the screen
    tft.setTextPadding(tft.textWidth("999", 4));
    // Draw the patch number in font 4
    tft.drawNumber(currentPatchNumber, 119, 65, 4);

    if (!paintItBlack) {
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
    }

    tft.setTextPadding(tft.textWidth("XXXXXXXXXXXXXXXXXXXXXXXXX", 1));
    // Draw the patch name in font 1
    string name = synthesizer.getPatchName();
    rtrim(name, ' ');
    tft.drawString(name.c_str(), 119, 120, 1);

    // Reset text padding and datum to 0 otherwise all future rendered strings will use it!
    tft.setTextPadding(0);
    tft.setTextDatum(0);
}

void clearMainScreen() {
    tft.fillScreen(TFT_BLACK);
    tft.fillRect(0, 0, 240, 26, MY_ORANGE);
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

void shortcutButtonChanged(Button *btn, bool released) {
    Serial.print("Shortcut-button #");
    Serial.print(btn->id);
    Serial.print(" ");
    Serial.println((released) ? "RELEASED" : "PRESSED");

    if (!released) {
        if (activeShortcut > 0) {
            parameterController.clearScreen();
        }

        activeShortcut = (shiftButtonPushed && btn->id <= 4) ? btn->id + 8 : btn->id;

        Serial.print("Active Shortcut: ");
        Serial.println(activeShortcut);
        for (auto &shortcutButton : shortcutButtons) {
            shortcutButton->setLED(shortcutButton->id == btn->id);
        }

        displayPatchInfo(true);

        parameterController.setSection(activeShortcut);
    }
}

void mainButtonChanged(Button *btn, bool released) {
    Serial.print("Main-button #");
    Serial.print(btn->id);
    Serial.print(" ");
    Serial.println((released) ? "RELEASED" : "PRESSED");

    switch (btn->id) {
        case SHIFT_BUTTON:
            shiftButtonPushed = !released;
            break;
        case ESC_BUTTON:
            if (!released) {
                if (activeShortcut > 0) {
                    parameterController.clearScreen();
                    clearShortcut();
                    displayPatchInfo();
                }
                parameterController.setDefaultSection();
            }
    }
}

void clearShortcut() {
    activeShortcut = 0;
    for (auto &shortcutButton : shortcutButtons) {
        shortcutButton->setLED(false);
    }
}

void rotaryButtonChanged(Button *btn, bool released) {
    Serial.print("Rotary-button #");
    Serial.print(btn->id);
    Serial.print(" ");
    Serial.println((released) ? "RELEASED" : "PRESSED");
}

void upOrDownButtonChanged(Button *btn, bool released) {
    Serial.print((btn->id == UP_BUTTON) ? "Up" : "Down");
    Serial.print("-button");
    Serial.print(" ");
    Serial.println((released) ? "RELEASED" : "PRESSED");

    if (!released) {
        if (btn->id == UP_BUTTON) {
            parameterController.upButtonTapped();
        } else {
            parameterController.downButtonTapped();
        }
    }
}

void mainRotaryButtonChanged(bool released) {
    Serial.print("MAIN-Rotary-button ");
    Serial.println((released) ? "RELEASED" : "PRESSED");

}
