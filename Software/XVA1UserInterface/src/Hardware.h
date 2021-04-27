//
// Created by André Mathlener on 05/04/2021.
//

#ifndef XVA1USERINTERFACE_HARDWARE_H
#define XVA1USERINTERFACE_HARDWARE_H

#include <Rotary.h>
#include <RotaryEncOverMCP.h>
#include "Button.h"
#include "Multiplexer.h"
#include "Synthesizer.h"
#include "ParameterController.h"

#define MAIN_ROTARY_BUTTON  0
#define MENU_BUTTON         1
#define SAVE_BUTTON         2
#define ESC_BUTTON          3
#define SHIFT_BUTTON        4

#define UP_BUTTON           1
#define DOWN_BUTTON         2

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     (-1) // Reset pin # (or -1 if sharing Arduino reset pin)

#define MAIN_ROTARY_BTN_PIN 27

// Pins for MCP23017
#define GPA0 0
#define GPA1 1
#define GPA2 2
#define GPA3 3
#define GPA4 4
#define GPA5 5
#define GPA6 6
#define GPA7 7
#define GPB0 8
#define GPB1 9
#define GPB2 10
#define GPB3 11
#define GPB4 12
#define GPB5 13
#define GPB6 14
#define GPB7 15

/* Function prototypes */

void mainRotaryButtonChanged(bool released);

void mainButtonChanged(Button *btn, bool released);

void shortcutButtonChanged(Button *btn, bool released);

void rotaryButtonChanged(Button *btn, bool released);

void upOrDownButtonChanged(Button *btn, bool released);

void rotaryEncoderChanged(bool clockwise, int id);

// TCA9548A Multiplexer
Multiplexer multiplexer = Multiplexer(0x70);

// I2C MCP23017 GPIO expanders
Adafruit_MCP23017 mcp1;
Adafruit_MCP23017 mcp2;
Adafruit_MCP23017 mcp3;

//Array of pointers of all MCPs
Adafruit_MCP23017 *allMCPs[] = {&mcp1, &mcp2, &mcp3};


// OLED display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// TFT display
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h


Rotary mainRotaryEncoder = Rotary(25, 26);

/* Array of all rotary encoders and their pins */
RotaryEncOverMCP rotaryEncoders[] = {
        // outputA,B on GPA7,GPA6, register with callback and ID=1
        RotaryEncOverMCP(&mcp1, GPB5, GPB4, &rotaryEncoderChanged, 1),
        RotaryEncOverMCP(&mcp1, GPA2, GPA3, &rotaryEncoderChanged, 2),
        RotaryEncOverMCP(&mcp1, GPB2, GPB1, &rotaryEncoderChanged, 3),
        RotaryEncOverMCP(&mcp1, GPA5, GPA6, &rotaryEncoderChanged, 4),
        RotaryEncOverMCP(&mcp2, GPB7, GPB6, &rotaryEncoderChanged, 5),
        RotaryEncOverMCP(&mcp2, GPA0, GPA1, &rotaryEncoderChanged, 6),
        RotaryEncOverMCP(&mcp2, GPB4, GPB3, &rotaryEncoderChanged, 7),
        RotaryEncOverMCP(&mcp2, GPA3, GPA4, &rotaryEncoderChanged, 8),
};

Button menuButton = Button(&mcp1, GPB7, MENU_BUTTON, &mainButtonChanged);
Button saveButton = Button(&mcp1, GPB6, SAVE_BUTTON, &mainButtonChanged);
Button escButton = Button(&mcp1, GPA0, ESC_BUTTON, &mainButtonChanged);
Button shiftButton = Button(&mcp1, GPA1, SHIFT_BUTTON, &mainButtonChanged);

Button *mainButtons[] = {
        &menuButton, &saveButton, &escButton, &shiftButton,
};

LEDButton shortcutButton1 = LEDButton(&mcp3, GPB7, GPB6, 1, &shortcutButtonChanged);
LEDButton shortcutButton2 = LEDButton(&mcp3, GPB5, GPB4, 2, &shortcutButtonChanged);
LEDButton shortcutButton3 = LEDButton(&mcp3, GPB3, GPB2, 3, &shortcutButtonChanged);
LEDButton shortcutButton4 = LEDButton(&mcp3, GPB1, GPB0, 4, &shortcutButtonChanged);
LEDButton shortcutButton5 = LEDButton(&mcp3, GPA0, GPA1, 5, &shortcutButtonChanged);
LEDButton shortcutButton6 = LEDButton(&mcp3, GPA2, GPA3, 6, &shortcutButtonChanged);
LEDButton shortcutButton7 = LEDButton(&mcp3, GPA4, GPA5, 7, &shortcutButtonChanged);
LEDButton shortcutButton8 = LEDButton(&mcp3, GPA6, GPA7, 8, &shortcutButtonChanged);

LEDButton *shortcutButtons[] = {
        &shortcutButton1, &shortcutButton2, &shortcutButton3, &shortcutButton4,
        &shortcutButton5, &shortcutButton6, &shortcutButton7, &shortcutButton8
};

Button rotaryButton1 = Button(&mcp1, GPB3, 1, &rotaryButtonChanged);
Button rotaryButton2 = Button(&mcp1, GPA4, 2, &rotaryButtonChanged);
Button rotaryButton3 = Button(&mcp1, GPB0, 3, &rotaryButtonChanged);
Button rotaryButton4 = Button(&mcp1, GPA7, 4, &rotaryButtonChanged);
Button rotaryButton5 = Button(&mcp2, GPB5, 5, &rotaryButtonChanged);
Button rotaryButton6 = Button(&mcp2, GPA2, 6, &rotaryButtonChanged);
Button rotaryButton7 = Button(&mcp2, GPB2, 7, &rotaryButtonChanged);
Button rotaryButton8 = Button(&mcp2, GPA5, 8, &rotaryButtonChanged);

LEDButton upButton = LEDButton(&mcp2, GPB1, GPB0, 1, &upOrDownButtonChanged);
LEDButton downButton = LEDButton(&mcp2, GPA6, GPA7, 2, &upOrDownButtonChanged);

Button *allButtons[] = {
        &menuButton, &saveButton, &escButton, &shiftButton,
        &shortcutButton1, &shortcutButton2, &shortcutButton3, &shortcutButton4,
        &shortcutButton5, &shortcutButton6, &shortcutButton7, &shortcutButton8,
        &rotaryButton1, &rotaryButton2, &rotaryButton3, &rotaryButton4,
        &rotaryButton5, &rotaryButton6, &rotaryButton7, &rotaryButton8,
        &upButton, &downButton
};

Synthesizer synthesizer;
ParameterController parameterController = ParameterController(&synthesizer, &multiplexer, &tft, &display, &upButton, &downButton);

#endif //XVA1USERINTERFACE_HARDWARE_H
