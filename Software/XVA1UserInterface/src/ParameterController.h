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
#include "SectionFactory.h"
#include "Globals.h"

class ParameterController {
private:
    Synthesizer *synthesizer;
    Multiplexer *multiplexer;
    TFT_eSPI *tft;
    Adafruit_SSD1306 *display;
    LEDButton *upButton;
    LEDButton *downButton;

    const int LINE_HEIGHT = 25;

    Section section = SectionFactory().createDefaultSection();
    int parameterIndices[8];

    int currentPageNumber = 0;
    int currentSubSectionNumber = 0;
    Section subSection = Section("empty");

    bool shouldShowEnvelopes = false;
    const uint16_t envelopeColors[3] = { TFT_BLUE, TFT_MAGENTA, TFT_YELLOW };
    TaskHandle_t displayEnvelopesTaskHandle = nullptr;

    void clearParameters();

    void setActivePage(int pageNumber);

    void setActiveSubSection(int pageNumber);

    void displayActivePage();

    void displayParameters();

    void handleParameterChange(int index, bool clockwise, int speed);

    void displayTwinParameters(int index1, int index2, int displayNumber);

    void displayTwinParameters(string title1, string value1, string title2, string value2, int displayNumber);

    void drawCenteredText(string buf, int x, int y);

    string getDisplayValue(int parameterIndex);

    Section *getSubSection();

    void displaySubSections();
    void displaySubSections(bool paintItBlack);

    void clearCurrentSubsection();

    void displayCurrentSubsection();

    void clearEnvelopes();

    void displayEnvelopes();

    void displayEnvelope(const Envelope &envelope, uint16_t color);

    static void displayEnvelopesTask(void *parameter);

public:
    ParameterController(Synthesizer *synthesizer, Multiplexer *multiplexer, TFT_eSPI *tft, Adafruit_SSD1306 *display,
                        LEDButton *upButton, LEDButton *downButton);

    void setSection(int sectionNumber);
    void setSection(int sectionNumber, bool showSubSections);

    void setDefaultSection();

    bool rotaryEncoderChanged(int id, bool clockwise, int speed);

    bool rotaryEncoderButtonChanged(int id, bool released);

    void upButtonTapped();

    void downButtonTapped();

    void clearScreen();

    Section createSection(int sectionNumber);

    string to_string(int value);
};


#endif //XVA1USERINTERFACE_PARAMETERCONTROLLER_H
