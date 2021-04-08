//
// Created by André Mathlener on 08/04/2021.
//

#ifndef XVA1USERINTERFACE_PARAMETERCONTROLLER_H
#define XVA1USERINTERFACE_PARAMETERCONTROLLER_H


#include <TFT_eSPI.h>
#include <Adafruit_SSD1306.h>
#include "Synthesizer.h"
#include "Multiplexer.h"
#include "Section.h"
#include "LEDButton.h"

class ParameterController {
private:
    Synthesizer *synthesizer;
    Multiplexer *multiplexer;
    TFT_eSPI *tft;
    Adafruit_SSD1306 *display;
    LEDButton *upButton;
    LEDButton *downButton;

    Section *section = nullptr;
    int parameterIndices[8];

    int activePage = 1;

    void clearParameters();
    void setActivePage(int pageNumber);
    void showActivePage();

public:
    ParameterController(Synthesizer *synthesizer, Multiplexer *multiplexer, TFT_eSPI *tft, Adafruit_SSD1306 *display,
                        LEDButton *upButton, LEDButton *downButton);

    void setSection(Section *pSection);

    void rotaryEncoderChanged(int id, bool clockwise, int speed);
    void rotaryEncoderButtonChanged(int id, bool released);
    void upButtonTapped();
    void downButtonTapped();

};


#endif //XVA1USERINTERFACE_PARAMETERCONTROLLER_H
