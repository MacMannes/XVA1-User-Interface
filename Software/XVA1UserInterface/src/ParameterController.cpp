//
// Created by André Mathlener on 08/04/2021.
//

#include "ParameterController.h"
#include "Globals.h"

ParameterController::ParameterController(Synthesizer *synthesizer, Multiplexer *multiplexer, TFT_eSPI *tft,
                                         Adafruit_SSD1306 *display, LEDButton *upButton, LEDButton *downButton)
        : synthesizer(synthesizer), multiplexer(multiplexer), tft(tft), display(display),
          upButton(upButton), downButton(downButton) {
    clearParameters();
}

void ParameterController::upButtonTapped() {
    if (section == nullptr) return;

    if (currentPageNumber > 0) {
        int newPage = currentPageNumber - 1;
        setActivePage(newPage);
    }
}

void ParameterController::downButtonTapped() {
    if (section == nullptr) return;

    if (currentPageNumber < getSubSection()->getNumberOfPages() - 1) {
        int newPage = currentPageNumber + 1;
        setActivePage(newPage);
    }
}

void ParameterController::setDefaultSection() {
    setSection(SectionFactory().createDefaultSection(), false);
}

void ParameterController::setSection(Section *pSection) {
    setSection(pSection, true);
}

void ParameterController::setSection(Section *pSection, bool showSubSections) {
    SerialUSB.print(F("Setting active section: "));
    SerialUSB.println(pSection->getName().c_str());

    subSection = Section("empty");
    delete section;
    section = pSection;
    currentSubSectionNumber = 0;

    if (section == nullptr) {
        upButton->setLED(false);
        downButton->setLED(false);
        clearParameters();
        displayParameters();
    } else {
        clearCurrentSubsection();
        setActivePage(0);

        if (showSubSections) {
            displaySubSections();
        }
    }
}

void ParameterController::clearParameters() {
    for (auto &parameter : parameterIndices) {
        parameter = -1;
    }
}

void ParameterController::setActivePage(int pageNumber) {
    if (section == nullptr) return;

    if (pageNumber < 0 && pageNumber > getSubSection()->getNumberOfPages()) return;

    if (pageNumber != currentPageNumber) {
        SerialUSB.print(F("Setting active page: "));
        SerialUSB.println(pageNumber);
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

    if (section->getSubSections().size() > 0 && !section->hasVirtualSubSections()) {
        subSection = section->getSubSections().at(subSectionNumber);
    }
    currentSubSectionNumber = subSectionNumber;
    currentPageNumber = 0;

    displayCurrentSubsection();
    setActivePage(currentPageNumber); // This redraws all parameters
}

void ParameterController::displayActivePage() {
    if (section == nullptr) {
        upButton->setLED(false);
        downButton->setLED(false);
        return;
    };

    int numberOfPages = getSubSection()->getNumberOfPages();
    upButton->setLED(numberOfPages > 1 && currentPageNumber > 0);
    downButton->setLED(numberOfPages > 1 && currentPageNumber < numberOfPages - 1);
}

bool ParameterController::rotaryEncoderChanged(int id, bool clockwise, int speed) {
    if (section == nullptr) return false;

    if (id == 0) {
        int numberOfSubSections = section->getNumberOfSubSections();
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
            return true;
        }
    }

    return false;
}

bool ParameterController::rotaryEncoderButtonChanged(int id, bool released) {
    if (section == nullptr) return false;

    return false;
}

void ParameterController::handleParameterChange(int index, bool clockwise, int speed) {
    SynthParameter parameter = getSubSection()->getParameters()[index];
    int currentValue;

    int subIndex = (section->hasVirtualSubSections()) ? currentSubSectionNumber : 0;
    SerialUSB.print("subIndex: ");
    SerialUSB.println(subIndex);

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

            SerialUSB.print("Byte value: ");
            SerialUSB.println(value);
            SerialUSB.print("Bit-nr: ");
            SerialUSB.println(parameter.getBitNumber(subIndex));
            SerialUSB.print("Bit value: ");
            SerialUSB.println(currentValue);

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
    int subIndex = (section->hasVirtualSubSections()) ? currentSubSectionNumber : 0;

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

        int subIndex = (section->hasVirtualSubSections()) ? currentSubSectionNumber : 0;
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
                    string MIDI_NOTES[] = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };

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
    if (section->getSubSections().size() > 0) {
        subSection = section->getSubSections().at(currentSubSectionNumber);
        return &subSection;
    }

    return section;
}

void ParameterController::displaySubSections() {
    displaySubSections(false);
}

void ParameterController::displaySubSections(bool paintItBlack) {
    SerialUSB.print("displaySubSections(");
    SerialUSB.print((paintItBlack) ? "true" : "false");
    SerialUSB.println(")");

    if (section == nullptr) return;

    tft->setTextPadding(0);
    tft->setTextSize(2);

    tft->setTextColor(paintItBlack ? MY_ORANGE : TFT_WHITE);

    tft->setTextDatum(1);
    tft->drawString(section->getName().c_str(), 119, 4, 1);
    tft->setTextDatum(0);

    int lineNumber = 0;

    tft->setTextColor(paintItBlack ? TFT_BLACK : TFT_WHITE);

    for (auto &title : section->getSubSectionTitles()) {
        if (!paintItBlack) {
            tft->setTextColor((lineNumber == currentSubSectionNumber) ? TFT_WHITE : TFT_GREY);
        }
        if (lineNumber == currentSubSectionNumber) {
            tft->drawString(">", 0, 40 + LINE_HEIGHT * currentSubSectionNumber, 1);
        }

        tft->drawString(title.c_str(), 20, 40 + LINE_HEIGHT * lineNumber, 1);
        lineNumber++;
    }
}

void ParameterController::clearCurrentSubsection() {
    if (section == nullptr || section->getNumberOfSubSections() == 0) return;

    tft->setTextColor(TFT_BLACK);
    tft->drawString(">", 0, 40 + LINE_HEIGHT * currentSubSectionNumber, 1);
    tft->setTextColor(TFT_GREY);
    tft->drawString(section->getSubSectionTitles().at(currentSubSectionNumber).c_str(), 20,
                    40 + LINE_HEIGHT * currentSubSectionNumber, 1);
}

void ParameterController::displayCurrentSubsection() {
    tft->setTextColor(TFT_WHITE);
    tft->drawString(">", 0, 40 + LINE_HEIGHT * currentSubSectionNumber, 1);
    tft->drawString(section->getSubSectionTitles().at(currentSubSectionNumber).c_str(), 20,
                    40 + LINE_HEIGHT * currentSubSectionNumber, 1);
}

void ParameterController::clearScreen() {
    clearCurrentSubsection();
    displaySubSections(true);
}





