#include <Arduino.h>

#include <TFT_eSPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>

#include "SynthParameter.h"
#include "../lib/RotaryEncOverMCP/Adafruit_MCP23017.h"
#include "../lib/RotaryEncOverMCP/RotaryEncOverMCP.h"
#include "Button.h"
#include "LEDButton.h"

#define MUX_ADDRESS 0x70 // TCA9548A Multiplexer address

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

#define MENU_BUTTON     1
#define SAVE_BUTTON     2
#define ESC_BUTTON      3
#define SHIFT_BUTTON    4

#define ROTARY_BTN1_PIN 11
#define ROTARY_BTN2_PIN 4

/* I2C MCP23017 GPIO expanders */
Adafruit_MCP23017 mcp1;
Adafruit_MCP23017 mcp2;
Adafruit_MCP23017 mcp3;

//Array of pointers of all MCPs (for now, there's only 1)
Adafruit_MCP23017 *allMCPs[] = {&mcp1, &mcp2, &mcp3};

/* function prototypes */
void mainButtonChanged(Button *btn, bool released);

void shortcutButtonChanged(Button *btn, bool released);

void rotaryButtonChanged(Button *btn, bool released);

void rotaryEncoderChanged(bool clockwise, int id);

void handleMainEncoder(bool clockwise);

void handleParameterChange(SynthParameter *parameter, bool clockwise, int speed);

void displayTwinParameters(SynthParameter *parameter1, SynthParameter *parameter2, int displayNumber);

void displayTwinParameters(char *title1, char *value1, char *title2, char *value2, int displayNumber);

void initOLEDDisplays();

void pollAllMCPs();

void readButtons();

void selectPatchOnSynth(int number);

void getPatchDataFromSynth();

void displayPatchInfo();

void initButtons();

void setParameter(int number, int value);

Rotary mainRotaryEncoder = Rotary(2, 1);

/* Array of all rotary encoders and their pins */
RotaryEncOverMCP rotaryEncoders[] = {
        // outputA,B on GPA7,GPA6, register with callback and ID=1
        RotaryEncOverMCP(&mcp1, 10, 9, &rotaryEncoderChanged, 0),
        RotaryEncOverMCP(&mcp1, 13, 12, &rotaryEncoderChanged, 1),
        RotaryEncOverMCP(&mcp1, 2, 3, &rotaryEncoderChanged, 2)
};

Button menuButton = Button(&mcp1, 15, MENU_BUTTON, &mainButtonChanged);
Button saveButton = Button(&mcp1, 14, SAVE_BUTTON, &mainButtonChanged);
Button escButton = Button(&mcp1, 0, ESC_BUTTON, &mainButtonChanged);
Button shiftButton = Button(&mcp1, 1, SHIFT_BUTTON, &mainButtonChanged);

Button *mainButtons[] = {
        &menuButton, &saveButton, &escButton, &shiftButton,
};

LEDButton shortcutButton1 = LEDButton(&mcp3, 15, 14, 1, &shortcutButtonChanged);
LEDButton shortcutButton2 = LEDButton(&mcp3, 13, 12, 2, &shortcutButtonChanged);
LEDButton shortcutButton3 = LEDButton(&mcp3, 11, 10, 3, &shortcutButtonChanged);
LEDButton shortcutButton4 = LEDButton(&mcp3, 9, 8, 4, &shortcutButtonChanged);
LEDButton shortcutButton5 = LEDButton(&mcp3, 0, 1, 5, &shortcutButtonChanged);
LEDButton shortcutButton6 = LEDButton(&mcp3, 2, 3, 6, &shortcutButtonChanged);
LEDButton shortcutButton7 = LEDButton(&mcp3, 4, 5, 7, &shortcutButtonChanged);
LEDButton shortcutButton8 = LEDButton(&mcp3, 6, 7, 8, &shortcutButtonChanged);

LEDButton *shortcutButtons[] = {
        &shortcutButton1, &shortcutButton2, &shortcutButton3, &shortcutButton4,
        &shortcutButton5, &shortcutButton6, &shortcutButton7, &shortcutButton8
};

Button rotaryButton1 = Button(&mcp1, 11, 1, &rotaryButtonChanged);
Button rotaryButton2 = Button(&mcp1, 4, 2, &rotaryButtonChanged);
Button rotaryButton3 = Button(&mcp1, 8, 3, &rotaryButtonChanged);
Button rotaryButton4 = Button(&mcp1, 7, 4, &rotaryButtonChanged);
Button rotaryButton5 = Button(&mcp2, 13, 5, &rotaryButtonChanged);
Button rotaryButton6 = Button(&mcp2, 2, 6, &rotaryButtonChanged);
Button rotaryButton7 = Button(&mcp2, 10, 7, &rotaryButtonChanged);
Button rotaryButton8 = Button(&mcp2, 5, 8, &rotaryButtonChanged);

Button *allButtons[] = {
        &menuButton, &saveButton, &escButton, &shiftButton,
        &shortcutButton1, &shortcutButton2, &shortcutButton3, &shortcutButton4,
        &shortcutButton5, &shortcutButton6, &shortcutButton7, &shortcutButton8,
        &rotaryButton1, &rotaryButton2, &rotaryButton3, &rotaryButton4,
        &rotaryButton5, &rotaryButton6, &rotaryButton7, &rotaryButton8
};

// Initialize I2C buses using TCA9548A I2C Multiplexer
void selectMultiplexerChannel(uint8_t i2c_bus) {
    if (i2c_bus > 7) return;
    Wire.beginTransmission(MUX_ADDRESS);
    Wire.write(1 << i2c_bus);
    Wire.endTransmission();
}

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int MAX = 128;
const int MIN = 1;
int currentPatchNumber = MIN;
String currentPatchName = "";
byte currentPatchData[512];

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

#define TFT_GREY 0x5AEB // New colour

struct SynthParameter param1;
struct SynthParameter param2;
struct SynthParameter param3;
struct SynthParameter param4;

unsigned long lastTransition;
unsigned long revolutionTime = 0;

int activeShortcut = 0;

bool shiftButtonPushed = false;

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
    if (shiftButtonPushed) {
        if (id == 1) {
            handleParameterChange(&param3, clockwise, speed);
            displayTwinParameters(&param3, &param4, 1);
        }
        if (id == 2) {
            handleParameterChange(&param4, clockwise, speed);
            displayTwinParameters(&param3, &param4, 1);
        }
    } else {
        if (id == 1) {
            handleParameterChange(&param1, clockwise, speed);
            displayTwinParameters(&param1, &param2, 0);
        }
        if (id == 2) {
            handleParameterChange(&param2, clockwise, speed);
            displayTwinParameters(&param1, &param2, 0);
        }
    }
}


void setup() {
    SerialUSB.begin(115200);

    //while the serial stream is not open, do nothing:
//     while (!SerialUSB);

    SerialUSB.println("\n");
    SerialUSB.println("===================");
    SerialUSB.println("XVA1 User Interface");
    SerialUSB.println("===================\n");

//    strcpy(param1.name, "FilterType");
//    param1.number = 71;
//    param1.min = 0;
//    param1.max = 21;
//    param1.descriptions[0] = "Bypass";
//    param1.descriptions[1] = "1P_LowPass";
//    param1.descriptions[2] = "2P_LowPass";
//    param1.descriptions[3] = "3P_LowPass";
//    param1.descriptions[4] = "4P_LowPass";
//    param1.descriptions[5] = "1P_HighPass";
//    param1.descriptions[6] = "2P_HighPass";
//    param1.descriptions[7] = "3P_HighPass";
//    param1.descriptions[8] = "4P_HighPass";


    strcpy(param1.name, "Sequencer");
    param1.number = 428;
    param1.min = 0;
    param1.max = 1;
    param1.descriptions[0] = "OFF";
    param1.descriptions[1] = "ON";

    strcpy(param2.name, "Cutoff");
    param2.number = 72;
    param2.min = 0;
    param2.max = 255;

    strcpy(param3.name, "PerfCtl1");
    param3.type = PERFORMANCE_CTRL;
    param3.number = 400;
    param3.number2 = 401;
    param3.min = 0;
    param3.max = 511;

    strcpy(param4.name, "PerfCtl2");
    param4.type = PERFORMANCE_CTRL;
    param4.number = 402;
    param4.number2 = 403;
    param4.min = 0;
    param4.max = 511;

//    strcpy(param1.name, "ARP_MODE");
//    param1.number = 450;
//    param1.min = 0;
//    param1.max = 5;
//    strcpy(param2.name, "Octaves");
//    param2.number = 454;
//    param2.min = 0;
//    param2.max = 5;


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

    tft.setCursor(0, 0, 2);
    // Set the font colour to be white with a black background, set text size multiplier to 1
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(1);
    tft.println("XVA1 Synthesizer");


    selectPatchOnSynth(currentPatchNumber);
    getPatchDataFromSynth();
    displayPatchInfo();

    mainRotaryEncoder.begin(true);
}


void loop() {
    unsigned char result = mainRotaryEncoder.process();
    if (result) {
        handleMainEncoder(result == DIR_CW);
    }

    pollAllMCPs();
}


void initOLEDDisplays() {
    for (int d = 0; d < 4; d++) {
        selectMultiplexerChannel(d);
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
}

void handleMainEncoder(bool clockwise) {
    int oldValue = currentPatchNumber;

    if (clockwise) {
        if (currentPatchNumber < MAX) {
            currentPatchNumber++;
        }
    } else {
        if (currentPatchNumber > MIN) {
            currentPatchNumber--;
        }
    }

    SerialUSB.print("Selecting patch: ");
    SerialUSB.println(currentPatchNumber);

    if (currentPatchNumber != oldValue) {
        selectPatchOnSynth(currentPatchNumber);
        getPatchDataFromSynth();
        displayPatchInfo();
    }
}

void selectPatchOnSynth(int patchNumber) {
    int synthPatchNumber = patchNumber - 1;

    SerialUSB.print("Selecting patch #");
    SerialUSB.print(synthPatchNumber);
    SerialUSB.print(" on Synth...");

    Serial1.write('r'); // 'r' = Read program
    Serial1.write(synthPatchNumber);


    int read_status;
    int bytesRead = 0;
    int retry = 0;
    while (bytesRead == 0 && retry != 100) {
        if (Serial1.available()) {
            read_status = Serial1.read();
            bytesRead++;
            retry = 0;
        } else {
            retry++;
            delay(10);
        }
    }

    SerialUSB.print("Status=");
    SerialUSB.println(read_status, DEC);

}

void getPatchDataFromSynth() {

    Serial1.write('d'); // 'd' = Display program

    SerialUSB.println("Reading patch data from Synth...");

    byte rxBuffer[512];
    int bytesRead = 0;
    int retry = 0;
    while (bytesRead != 512 && retry != 100) {
        if (Serial1.available()) {
            byte b = Serial1.read();
            rxBuffer[bytesRead] = b;
            bytesRead++;
            retry = 0;
        } else {
            retry++;
            delay(10);
        }
    }

//    for (int i = 0; i < sizeof(rxBuffer); i++){
//      printHex(rxBuffer[i]);
//    }

    SerialUSB.println();

    String patchName = "";

    for (int i = 480; i < 505; i++) {
        patchName += (char) rxBuffer[i];
    }

    SerialUSB.print("Patch name: ");
    SerialUSB.println(patchName);
    SerialUSB.println();

    Serial1.flush();

    memcpy(currentPatchData, rxBuffer, 512);
    currentPatchName = patchName;
}

void displayPatchInfo() {
//  tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString("Patch", 0, 30, 1);

    tft.setTextColor(TFT_YELLOW, TFT_BLACK);

    // Set the padding to the maximum width that the digits could occupy in font 4
    // This ensures small numbers obliterate large ones on the screen
    tft.setTextPadding(tft.textWidth("999", 4));
    // Draw the patch number in font 4
    tft.drawNumber(currentPatchNumber, 0, 42, 4);

    tft.setTextColor(TFT_CYAN, TFT_BLACK);

    tft.setTextPadding(tft.textWidth("XXXXXXXXXXXXXXXXXXXXXXXXX", 2));
    // Draw the patch name in font 1
    tft.drawString(currentPatchName, 0, 75, 2);

    // Reset text padding to 0 otherwise all future rendered strings will use it!
    tft.setTextPadding(0);

    displayTwinParameters(&param1, &param2, 0);
    displayTwinParameters(&param3, &param4, 1);

}

void drawCenteredText(char *buf, int x, int y) {
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

    if (parameter1->type == PERFORMANCE_CTRL) {
        byte msb = currentPatchData[parameter1->number];
        byte lsb = currentPatchData[parameter1->number2];
        int combined = (msb << 7) + lsb;

        byte1 = (int) combined;
    } else {
        byte1 = (int) currentPatchData[parameter1->number];
    }

    if (parameter2->type == PERFORMANCE_CTRL) {
        byte msb = currentPatchData[parameter2->number];
        byte lsb = currentPatchData[parameter2->number2];
        int combined = (msb << 7) + lsb;

        byte2 = (int) combined;
    } else {
        byte2 = (int) currentPatchData[parameter2->number];
    }

    char printValue1[20];
    if (parameter1->type != PERFORMANCE_CTRL && byte1 < sizeof(parameter1->descriptions) &&
        parameter1->descriptions[byte1] != nullptr) {
        strcpy(printValue1, parameter1->descriptions[byte1]);
    } else {
        sprintf(printValue1, "%d", byte1);
    }
    char printValue2[20];
    if (parameter2->type != PERFORMANCE_CTRL && byte2 < sizeof(parameter2->descriptions) &&
        parameter2->descriptions[byte1] != nullptr) {
        strcpy(printValue2, parameter2->descriptions[byte2]);
    } else {
        sprintf(printValue2, "%d", byte2);
    }

    displayTwinParameters(parameter1->name, printValue1, parameter2->name, printValue2, displayNumber);
}

void displayTwinParameters(char *title1, char *value1, char *title2, char *value2, int displayNumber) {
    selectMultiplexerChannel(displayNumber);

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

    if (param->type == PERFORMANCE_CTRL) {
        byte msb = currentPatchData[param->number];
        byte lsb = currentPatchData[param->number2];
        int combined = (msb << 7) + lsb;
        currentValue = combined;
    } else {
        currentValue = currentPatchData[param->number];
    }
    int newValue = -1;

    if (clockwise) {
        if (currentValue < param->max) {
            newValue = currentValue + speed;
            if (newValue > param->max) {
                newValue = param->max;
            }
        }
    } else {
        if (currentValue > param->min) {
            newValue = currentValue - speed;
            if (newValue < param->min) {
                newValue = param->min;
            }
        }
    }


    if (newValue >= 0 && newValue != currentValue) {
        SerialUSB.print("New value: ");
        SerialUSB.println(newValue);
        if (param->type == PERFORMANCE_CTRL) {
            int msb = newValue >> 7;
            int lsb = newValue & 127;

            currentPatchData[param->number] = msb;
            currentPatchData[param->number2] = lsb;

            setParameter(param->number, msb);
            setParameter(param->number2, lsb);
        } else {
            currentPatchData[param->number] = newValue;

            setParameter(param->number, newValue);
        }
    }

}

void setParameter(int param, int value) {
    Serial1.write('s'); // 's' = Set Parameter

    if (param > 255) {
        // Parameters above 255 have a two-byte format: b1 = 255, b2 = x-256
        Serial1.write(255);
        Serial1.write(param - 256);
        Serial1.write(value);
    } else {
        Serial1.write(param);
        Serial1.write(value);
    }
}

void shortcutButtonChanged(Button *btn, bool released) {
    SerialUSB.print("Shortcut-button #");
    SerialUSB.print(btn->id);
    SerialUSB.print(" ");
    SerialUSB.println((released) ? "PRESSED" : "RELEASED");

    activeShortcut = (shiftButtonPushed && btn->id <= 4) ? btn->id + 8 : btn->id;

    if (released) {
        SerialUSB.print("Active Shortcut: ");
        SerialUSB.println(activeShortcut);
        for (auto &shortcutButton : shortcutButtons) {
            shortcutButton->setLED(shortcutButton->id == btn->id);
        }
    }
}

void mainButtonChanged(Button *btn, bool released) {
    SerialUSB.print("Main-button #");
    SerialUSB.print(btn->id);
    SerialUSB.print(" ");
    SerialUSB.println((released) ? "PRESSED" : "RELEASED");

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
            break;
    }
}

void rotaryButtonChanged(Button *btn, bool released) {
    SerialUSB.print("Rotary-button #");
    SerialUSB.print(btn->id);
    SerialUSB.print(" ");
    SerialUSB.println((released) ? "PRESSED" : "RELEASED");
}
