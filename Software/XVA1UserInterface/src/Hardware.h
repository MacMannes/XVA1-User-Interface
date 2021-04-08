//
// Created by André Mathlener on 05/04/2021.
//

#ifndef XVA1USERINTERFACE_HARDWARE_H
#define XVA1USERINTERFACE_HARDWARE_H

#include <Rotary.h>
#include <RotaryEncOverMCP.h>
#include "Button.h"
#include "Multiplexer.h"

#define MAIN_ROTARY_BUTTON  0
#define MENU_BUTTON         1
#define SAVE_BUTTON         2
#define ESC_BUTTON          3
#define SHIFT_BUTTON        4

#define UP_BUTTON           1
#define DOWN_BUTTON         2

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

#define TFT_GREY 0x5AEB // New colour
#define MY_ORANGE 0xFBA0 // New colour

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


Rotary mainRotaryEncoder = Rotary(1, 2);

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

LEDButton upButton = LEDButton(&mcp2, 9, 8, 1, &upOrDownButtonChanged);
LEDButton downButton = LEDButton(&mcp2, 6, 7, 2, &upOrDownButtonChanged);

Button *allButtons[] = {
        &menuButton, &saveButton, &escButton, &shiftButton,
        &shortcutButton1, &shortcutButton2, &shortcutButton3, &shortcutButton4,
        &shortcutButton5, &shortcutButton6, &shortcutButton7, &shortcutButton8,
        &rotaryButton1, &rotaryButton2, &rotaryButton3, &rotaryButton4,
        &rotaryButton5, &rotaryButton6, &rotaryButton7, &rotaryButton8,
        &upButton, &downButton
};

#endif //XVA1USERINTERFACE_HARDWARE_H
