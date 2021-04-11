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
#include "SynthParameterBuilder.h"

class ParameterController {
private:
    Synthesizer *synthesizer;
    Multiplexer *multiplexer;
    TFT_eSPI *tft;
    Adafruit_SSD1306 *display;
    LEDButton *upButton;
    LEDButton *downButton;

    Section *section = &defaultSection;
    int parameterIndices[8];

    int activePageNumber = 0;
    int activeSubSectionNumber = 0;
    Section subSection = Section("empty");

    void clearParameters();

    void setActivePage(int pageNumber);

    void displayActivePage();

    void displayParameters();

    void handleParameterChange(int index, bool clockwise, int speed);

    void displayTwinParameters(int index1, int index2, int displayNumber);

    void displayTwinParameters(string title1, string value1, string title2, string value2, int displayNumber);

    void drawCenteredText(string buf, int x, int y);

    string getDisplayValue(int parameterIndex);

    Section *getSection();

    Section defaultSection = Section(
            "Default",
            {
                    SynthParameterBuilder("Cutoff")
                            .number(72)
                            .build(),

                    SynthParameterBuilder("Resonance")
                            .number(77)
                            .build(),

                    SynthParameterBuilder("Sequencer")
                            .number(428)
                            .max(1)
                            .descriptions({"OFF", "ON"})
                            .build()
            }
    );

public:
    ParameterController(Synthesizer *synthesizer, Multiplexer *multiplexer, TFT_eSPI *tft, Adafruit_SSD1306 *display,
                        LEDButton *upButton, LEDButton *downButton);

    void setSection(Section *pSection);
    void setDefaultSection();

    void rotaryEncoderChanged(int id, bool clockwise, int speed);

    void rotaryEncoderButtonChanged(int id, bool released);

    void upButtonTapped();

    void downButtonTapped();

};


#endif //XVA1USERINTERFACE_PARAMETERCONTROLLER_H
