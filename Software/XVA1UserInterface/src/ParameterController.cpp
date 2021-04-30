//
// Created by André Mathlener on 08/04/2021.
//

#include <sstream>
#include "ParameterController.h"
#include "Globals.h"
#include "FreeMemory.h"
#include "AllSynthParameters.h"

ParameterController::ParameterController(Synthesizer *synthesizer, Multiplexer *multiplexer, TFT_eSPI *tft,
                                         Adafruit_SSD1306 *display, LEDButton *upButton, LEDButton *downButton)
        : synthesizer(synthesizer), multiplexer(multiplexer), tft(tft), display(display),
          upButton(upButton), downButton(downButton) {
    clearParameters();
}

void ParameterController::upButtonTapped() {
    if (currentPageNumber > 0) {
        int newPage = currentPageNumber - 1;
        setActivePage(newPage);
    }
}

void ParameterController::downButtonTapped() {
    if (currentPageNumber < getSubSection()->getNumberOfPages() - 1) {
        int newPage = currentPageNumber + 1;
        setActivePage(newPage);
    }
}

void ParameterController::setDefaultSection() {
    setSection(0, false);
}

void ParameterController::setSection(int sectionNumber) {
    setSection(sectionNumber, true);
}

void ParameterController::setSection(int sectionNumber, bool showSubSections) {
    shouldShowEnvelopes = (sectionNumber == 6);

    subSection = Section("empty");

    section = Section("empty"); // Ugly trick to release some memory
    section = createSection(sectionNumber);
    currentSubSectionNumber = 0;

    clearCurrentSubsection();
    setActivePage(0);

    if (showSubSections) {
        displaySubSections();

        Serial.print("freeMemory()=");
        Serial.println(freeMemory());
    }

    if (shouldShowEnvelopes) {
        displayEnvelopes();
    }
}

void ParameterController::clearParameters() {
    for (auto &parameter : parameterIndices) {
        parameter = -1;
    }
}

void ParameterController::setActivePage(int pageNumber) {
    if (pageNumber < 0 && pageNumber > getSubSection()->getNumberOfPages()) return;

    if (pageNumber != currentPageNumber) {
        Serial.print(F("Setting active page: "));
        Serial.println(pageNumber);
    }

    clearParameters();
    currentPageNumber = pageNumber;

    int start = (pageNumber * 8);
    int end = start + 7;
    if (end > getSubSection()->getParameters().size() - 1) {
        end = getSubSection()->getParameters().size() - 1;
    }

    int i = start;
    for (int &parameterIndex : parameterIndices) {
        parameterIndex = (i <= end && !getSubSection()->getParameters().at(i).getName().empty()) ? i : -1;
        i++;
    }

    displayActivePage();
    displayParameters();
}

void ParameterController::setActiveSubSection(int subSectionNumber) {
    clearCurrentSubsection();

    if (section.getSubSections().size() > 0 && !section.hasVirtualSubSections()) {
        subSection = section.getSubSections().at(subSectionNumber);
    }
    currentSubSectionNumber = subSectionNumber;
    currentPageNumber = 0;

    displayCurrentSubsection();
    setActivePage(currentPageNumber); // This redraws all parameters
}

void ParameterController::displayActivePage() {
    int numberOfPages = getSubSection()->getNumberOfPages();
    upButton->setLED(numberOfPages > 1 && currentPageNumber > 0);
    downButton->setLED(numberOfPages > 1 && currentPageNumber < numberOfPages - 1);
}

bool ParameterController::rotaryEncoderChanged(int id, bool clockwise, int speed) {
    if (id == 0) {
        int numberOfSubSections = section.getNumberOfSubSections();
        if (numberOfSubSections > 0) {
            if (clockwise) {
                if (currentSubSectionNumber + 1 < numberOfSubSections) {
                    setActiveSubSection(currentSubSectionNumber + 1);
                }
            } else {
                if (currentSubSectionNumber > 0) {
                    setActiveSubSection(currentSubSectionNumber - 1);
                }
            }
        }

        return true;
    } else {
        id--;
        int index = parameterIndices[id];
        if (index >= 0) {
            handleParameterChange(index, clockwise, speed);

            int index1 = (id % 2 == 0) ? id : id - 1;
            int index2 = index1 + 1;
            int displayNumber = (index1 / 2);

            displayTwinParameters(parameterIndices[index1], parameterIndices[index2], displayNumber);

            if (shouldShowEnvelopes) {
                displayEnvelopes();
            }

            return true;
        }
    }

    return false;
}

bool ParameterController::rotaryEncoderButtonChanged(int id, bool released) {
    return false;
}

void ParameterController::handleParameterChange(int index, bool clockwise, int speed) {
    SynthParameter parameter = getSubSection()->getParameters()[index];
    int currentValue;

    int subIndex = (section.hasVirtualSubSections()) ? currentSubSectionNumber : 0;
    Serial.print("subIndex: ");
    Serial.println(subIndex);

    switch (parameter.getType()) {
        case PERFORMANCE_CTRL: {
            byte msb = synthesizer->getParameter(parameter.getNumber(0));
            byte lsb = synthesizer->getParameter(parameter.getNumber(1));
            int combined = (msb << 7) + lsb;
            currentValue = combined;
            break;
        }
        case BITWISE: {
            int value = synthesizer->getParameter(parameter.getNumber());
            currentValue = bitRead(value, parameter.getBitNumber(subIndex));

            Serial.print("Byte value: ");
            Serial.println(value);
            Serial.print("Bit-nr: ");
            Serial.println(parameter.getBitNumber(subIndex));
            Serial.print("Bit value: ");
            Serial.println(currentValue);

            break;
        }
        default:
            currentValue = synthesizer->getParameter(parameter.getNumber(subIndex));
    }
    int newValue = -1;

    if (clockwise) {
        if (currentValue < parameter.getMax()) {
            newValue = currentValue + speed;
            if (newValue > parameter.getMax()) {
                newValue = parameter.getMax();
            }
        } else if (parameter.getMax() == 1) {
            newValue = 0;
        }
    } else {
        if (currentValue > parameter.getMin()) {
            newValue = currentValue - speed;
            if (newValue < parameter.getMin()) {
                newValue = parameter.getMin();
            }
        } else if (parameter.getMax() == 1) {
            newValue = 1;
        }
    }

    // Besides values 0 through 127, MIDI_NOTE can also have values 200, 201 and 255
    if (parameter.getType() == MIDI_NOTE && newValue > 127) {
        if (newValue != 200 && newValue != 201 && newValue != 255) {
            if (clockwise) {
                if (newValue < 200) {
                    newValue = 200;
                } else if (newValue < 255) {
                    newValue = 255;
                }
            } else {
                if (newValue < 200) {
                    newValue = 127;
                } else if (newValue < 255) {
                    newValue = 201;
                }
            }
        }
    }

    if (newValue >= 0 && newValue != currentValue) {
        switch (parameter.getType()) {
            case PERFORMANCE_CTRL: {
                int msb = newValue >> 7;
                int lsb = newValue & 127;

                synthesizer->setParameter(parameter.getNumber(0), msb);
                synthesizer->setParameter(parameter.getNumber(1), lsb);
                break;
            }
            case BITWISE: {
                int value = synthesizer->getParameter(parameter.getNumber());
                bitWrite(value, parameter.getBitNumber(subIndex), newValue);
                synthesizer->setParameter(parameter.getNumber(), value);

                break;
            }
            default:
                synthesizer->setParameter(parameter.getNumber(subIndex), newValue);
        }
    }
}

void ParameterController::displayTwinParameters(int index1, int index2, int displayNumber) {
    int subIndex = (section.hasVirtualSubSections()) ? currentSubSectionNumber : 0;

    string name1 = (index1 >= 0 && getSubSection()->getParameters()[index1].getNumber(subIndex) > 0)
                   ? getSubSection()->getParameters()[index1].getName() : "";
    string name2 = (index2 >= 0 && getSubSection()->getParameters()[index2].getNumber(subIndex) > 0)
                   ? getSubSection()->getParameters()[index2].getName() : "";

    displayTwinParameters(name1, getDisplayValue(index1), name2, getDisplayValue(index2), displayNumber);

}

void ParameterController::displayTwinParameters(string title1, string value1, string title2, string value2,
                                                int displayNumber) {
    multiplexer->selectChannel(displayNumber);

    display->clearDisplay();

    display->setTextSize(1);
    display->setTextColor(WHITE);
    drawCenteredText(title1, 64, 0);

    display->setTextSize(2);
    drawCenteredText(value1, 64, 12);

    if (!title1.empty() || !value1.empty() || !title2.empty() || !value2.empty()) {
        display->drawLine(0, 30, display->width() - 1, 30, WHITE);
    }

    display->setTextSize(1);
    drawCenteredText(title2, 64, 34);

    display->setTextSize(2);
    drawCenteredText(value2, 64, 47);

    display->display();
}

void ParameterController::displayParameters() {
    for (int i = 0; i < 4; ++i) {
        int index1 = i * 2;
        int index2 = index1 + 1;
        displayTwinParameters(parameterIndices[index1], parameterIndices[index2], i);
    }
}

void ParameterController::drawCenteredText(string buf, int x, int y) {
    int16_t x1, y1;
    uint16_t w, h;
    display->getTextBounds(buf.c_str(), 0, y, &x1, &y1, &w, &h); //calc width of new string
    if (x - w / 2 <= 0) {
        // Text won't fit. Set smallest text size and recompute
        display->setTextSize(1);
        display->getTextBounds(buf.c_str(), 0, y, &x1, &y1, &w, &h);
        display->setCursor(x - w / 2, y + (h / 2));
    } else {
        display->setCursor(x - w / 2, y);
    }
    display->print(buf.c_str());
}

string ParameterController::getDisplayValue(int parameterIndex) {
    string printValue = "";

    if (parameterIndex >= 0) {
        SynthParameter parameter = getSubSection()->getParameters()[parameterIndex];

        int subIndex = (section.hasVirtualSubSections()) ? currentSubSectionNumber : 0;
        if (parameter.getNumber(subIndex) < 0) return printValue;

        int value;
        switch (parameter.getType()) {
            case PERFORMANCE_CTRL: {
                byte msb = synthesizer->getParameter(parameter.getNumber(0));
                byte lsb = synthesizer->getParameter(parameter.getNumber(1));
                int combined = (msb << 7) + lsb;

                value = (int) combined;

                break;
            }
            case BITWISE: {
                int byte = synthesizer->getParameter(parameter.getNumber());
                value = bitRead(byte, parameter.getBitNumber(subIndex));

                break;
            }
            case CENTER_128: {
                value = (int) synthesizer->getParameter(parameter.getNumber(subIndex)) - 128;
                if (value > 0) {
                    printValue = "+" + to_string(value);
                }

                break;
            }
            case MIDI_NOTE: {
                value = (int) synthesizer->getParameter(parameter.getNumber(subIndex));
                if (value <= 127) {
                    string MIDI_NOTES[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

                    int octave = (value / 12) - 1;
                    int noteIndex = (value % 12);
                    printValue = MIDI_NOTES[noteIndex] + to_string(octave);
                } else if (value == 200) {
                    printValue = "Gate ON";
                } else if (value == 201) {
                    printValue = "Gate OFF";
                } else if (value == 255) {
                    printValue = "Note OFF";
                }
                break;
            }
            case ASCII_CHAR:
                value = (int) synthesizer->getParameter(parameter.getNumber(subIndex));
                printValue += value;
                break;
            default: {
                value = (int) synthesizer->getParameter(parameter.getNumber(subIndex));
            }
        };

        if (printValue.empty()) {
            if (value < parameter.getDescriptions().size()) {
                printValue = parameter.getDescriptions()[value];
            } else {
                printValue = to_string(value);
            }
        }
    }

    return printValue;
}

Section *ParameterController::getSubSection() {
    if (section.getSubSections().size() > 0) {
        subSection = section.getSubSections().at(currentSubSectionNumber);
        return &subSection;
    }

    return &section;
}

void ParameterController::displaySubSections() {
    displaySubSections(false);
}

void ParameterController::displaySubSections(bool paintItBlack) {
    Serial.print("displaySubSections(");
    Serial.print((paintItBlack) ? "true" : "false");
    Serial.println(")");

    tft->setTextPadding(0);
    tft->setTextSize(2);

    tft->setTextColor(paintItBlack ? MY_ORANGE : TFT_WHITE);

    tft->setTextDatum(1);
    tft->drawString(section.getName().c_str(), 119, 4, 1);
    tft->setTextDatum(0);

    int lineNumber = 0;

    tft->setTextColor(paintItBlack ? TFT_BLACK : TFT_WHITE);

    for (auto &title : section.getSubSectionTitles()) {
        if (!paintItBlack) {
            tft->setTextColor((lineNumber == currentSubSectionNumber) ? TFT_WHITE : TFT_GREY);
        }
        if (lineNumber == currentSubSectionNumber) {
            tft->drawString(">", 0, 40 + LINE_HEIGHT * currentSubSectionNumber, 1);
        }

        tft->drawString(title.c_str(), 20, 40 + LINE_HEIGHT * lineNumber, 1);

        if (shouldShowEnvelopes) {
            tft->setTextColor(paintItBlack ? TFT_BLACK : envelopeColors[lineNumber]);
            tft->drawString("*", 110, 40 + LINE_HEIGHT * lineNumber, 1);
        }

        lineNumber++;
    }

    if (lineNumber == 0) {
        tft->drawString(">", 0, 40, 1);
        tft->drawString("Main", 20, 40, 1);
    }

    if (paintItBlack && shouldShowEnvelopes) {
        clearEnvelopes();
    }
}

void ParameterController::clearCurrentSubsection() {
    if (section.getNumberOfSubSections() == 0) return;

    tft->setTextColor(TFT_BLACK);
    tft->drawString(">", 0, 40 + LINE_HEIGHT * currentSubSectionNumber, 1);
    tft->setTextColor(TFT_GREY);
    tft->drawString(section.getSubSectionTitles().at(currentSubSectionNumber).c_str(), 20,
                    40 + LINE_HEIGHT * currentSubSectionNumber, 1);
}

void ParameterController::displayCurrentSubsection() {
    if (section.getNumberOfSubSections() == 0) return;

    tft->setTextColor(TFT_WHITE);
    tft->drawString(">", 0, 40 + LINE_HEIGHT * currentSubSectionNumber, 1);
    tft->drawString(section.getSubSectionTitles().at(currentSubSectionNumber).c_str(), 20,
                    40 + LINE_HEIGHT * currentSubSectionNumber, 1);
}

void ParameterController::clearScreen() {
    clearCurrentSubsection();
    displaySubSections(true);
    clearEnvelopes();
}

Section ParameterController::createSection(int sectionNumber) {
    return sections[sectionNumber];
}

string ParameterController::to_string(int value) {
    stringstream temp;
    temp << value;
    return temp.str();
}

void ParameterController::displayEnvelopes() {
    clearEnvelopes();

    for (int i = 0; i < 3; ++i) {
        displayEnvelope(synthesizer->getEnvelopeValues(envelopes[i]), envelopeColors[i]);
    }
}

/**
 * The code for displaying the envelopes is adopted from https://github.com/architolk/fm-synth
 *
 * Written by architolk
 */
void ParameterController::displayEnvelope(const Envelope &env, uint16_t color) {
    float envheight = 80;
    float envpos = 130;
    float envwidth = 239;

    float x1, x2, y1, y2, yd, yq, xq, r0, r1, r2, r3, r4, r5, l0, l1, l2, l3, l4, l5;
    //Getting envelope parameters
    r0 = env.rate[0];
    r1 = 255 - env.rate[1];
    r2 = 255 - env.rate[2];
    r3 = 255 - env.rate[3];
    r4 = 255 - env.rate[4];
    r5 = 255 - env.rate[5];
    l0 = env.level[0];
    l1 = env.level[1];
    l2 = env.level[2];
    l3 = env.level[3];
    l4 = env.level[4];
    l5 = env.level[5];
    yq = envheight / 255.0; //Quotient bij maximale waarde van 63
    xq = envwidth /
         (255 + (r0 > 0 ? 255 : 0) + (r1 > 0 ? 255 : 0) + (r2 > 0 ? 255 : 0) + (r3 > 0 ? 255 : 0) + (r4 > 0 ? 255 : 0) +
          (r5 > 0 ? 255 : 0));
    yd = envpos;
    x1 = 0.0;
    x2 = x1 + xq * r0; //Delay
    y1 = yq * (255 - l0) + yd;
    y2 = yq * (255 - l0) + yd;
    tft->drawLine(x1, y1, x2, y2, color);
    x1 = x2;
    y1 = y2;
    x2 = x1 + xq * r1; //Attack
    y2 = yq * (255 - l1) + yd;
    tft->drawLine(x1, y1, x2, y2, color);
    x1 = x2;
    y1 = y2;
    x2 = x1 + xq * r2; //Decay-1
    y2 = yq * (255 - l2) + yd;
    tft->drawLine(x1, y1, x2, y2, color);
    x1 = x2;
    y1 = y2;
    x2 = x1 + xq * r3; //Decay-2
    y2 = yq * (255 - l3) + yd;
    tft->drawLine(x1, y1, x2, y2, color);
    x1 = x2;
    y1 = y2;
    x2 = x1 + envwidth - xq * (r0 + r1 + r2 + r3 + r4 + r5); //Sustain
    y2 = yq * (255 - l3) + yd;
    tft->drawLine(x1, y1 - 1, x2, y2 - 1, color);
    tft->drawLine(x1, y1, x2, y2, color);
    tft->drawLine(x1, y1 + 1, x2, y2 + 1, color);
    x1 = x2;
    y1 = y2;
    x2 = x1 + xq * r4; //Release-1
    y2 = yq * (255 - l4) + yd;
    tft->drawLine(x1, y1, x2, y2, color);
    x1 = x2;
    y1 = y2;
    x2 = x1 + xq * r5; //Release-2
    y2 = yq * (255 - l5) + yd;
    tft->drawLine(x1, y1, x2, y2, color);
}

void ParameterController::clearEnvelopes() {
    tft->fillRect(0, 120, 238, 119, TFT_BLACK);
}





