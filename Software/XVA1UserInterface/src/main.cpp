#include <Arduino.h>

#include <TFT_eSPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>

#include "SynthParameter.h"
#include "Button.h"
#include "SynthParameterBuilder.h"
#include "XVA1SynthParameters.h"
#include "Hardware.h"

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

void initButtons();

void clearShortcut();

void clearMainScreen();

void initMainScreen();

void initRotaryEncoders();

void setup() {
    SerialUSB.begin(115200);

    //while the serial stream is not open, do nothing:
//     while (!SerialUSB);

    SerialUSB.println("\n");
    SerialUSB.println("===================");
    SerialUSB.println("XVA1 User Interface");
    SerialUSB.println("===================\n");

    mcp1.begin(0);
    mcp2.begin(1);
    mcp3.begin(2);

    Serial1.begin(500000); // XVA1 Serial

    initMainScreen();
    clearMainScreen();

    initRotaryEncoders();
    initOLEDDisplays();
    initButtons();

    synthesizer.selectPatch(1);
    displayPatchInfo();
    parameterController.setDefaultSection();

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

    parameterController.rotaryEncoderChanged(id, clockwise, speed);
}

void initRotaryEncoders() {
    for (auto &rotaryEncoder : rotaryEncoders) {
        rotaryEncoder.init();
    }
}

void initMainScreen() {
    tft.init();
    tft.setRotation(0);  // 0 & 2 Portrait. 1 & 3 landscapeooooooo;;
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
        clearShortcut();
        parameterController.setDefaultSection();
    }
}

void displayPatchInfo() {
    int currentPatchNumber = synthesizer.getPatchNumber();

    tft.setCursor(0, 0, 1);

    // Set the font colour to be orange with a black background, set text size multiplier to 1
    tft.setTextColor(MY_ORANGE, TFT_BLACK);
    tft.setTextSize(2);
    tft.println("XVA1 Synthesizer");


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
}

void clearMainScreen() { tft.fillScreen(TFT_BLACK); }

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
                clearShortcut();
            }
            parameterController.setDefaultSection();
    }
}

void clearShortcut() {
    activeShortcut = 0;
    for (auto &shortcutButton : shortcutButtons) {
        shortcutButton->setLED(false);
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
