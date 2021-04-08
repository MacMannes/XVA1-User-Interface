//
// Created by André Mathlener on 08/04/2021.
//

#include "ParameterController.h"

ParameterController::ParameterController(Synthesizer *synthesizer, Multiplexer *multiplexer, TFT_eSPI *tft,
                                         Adafruit_SSD1306 *display, LEDButton *upButton, LEDButton *downButton)
        : synthesizer(synthesizer), multiplexer(multiplexer), tft(tft), display(display),
          upButton(upButton), downButton(downButton) {
    clearParameters();
}

void ParameterController::rotaryEncoderChanged(int id, bool clockwise, int speed) {
    if (section == nullptr) return;

}

void ParameterController::rotaryEncoderButtonChanged(int id, bool released) {
    if (section == nullptr) return;

}

void ParameterController::upButtonTapped() {
    if (section == nullptr) return;

    if (activePage > 0) {
        int newPage = activePage - 1;
        setActivePage(newPage);
    }
}

void ParameterController::downButtonTapped() {
    if (section == nullptr) return;

    if (activePage < section->getNumberOfPages()) {
        int newPage = activePage + 1;
        setActivePage(newPage);
    }
}

void ParameterController::setSection(Section *pSection) {
    SerialUSB.print("Setting active section: ");
    SerialUSB.println((pSection != nullptr) ? pSection->getName().c_str() : "null");

    ParameterController::section = pSection;

    if (section == nullptr) {
        upButton->setLED(false);
        downButton->setLED(false);
    } else {
        SerialUSB.print("Number of subsections: ");
        SerialUSB.println(section->getNumberOfPages());

        for (auto &title : section->getSubSectionTitles()) {
            SerialUSB.print(" - ");
            SerialUSB.println(title.c_str());
        }

        SerialUSB.print("Number of parameters: ");
        SerialUSB.println(section->getParameters().size());
        SerialUSB.print("Number of pages: ");
        SerialUSB.println(section->getNumberOfPages());
    }

    setActivePage(1);
}

void ParameterController::clearParameters() {
    for (auto &parameter : parameterIndices) {
        parameter = -1;
    }
}

void ParameterController::setActivePage(int pageNumber) {
    SerialUSB.print("Setting active page: ");
    SerialUSB.println(pageNumber);

    if (section == nullptr) return;

    clearParameters();
    activePage = pageNumber;

    int start = (pageNumber * 8) - 8;
    int end = start + 7;
    if (end > section->getParameters().size() - 1) {
        end = section->getParameters().size() - 1;
    }

    SerialUSB.print(" - start: ");
    SerialUSB.println(start);
    SerialUSB.print(" - end: ");
    SerialUSB.println(end);

    int i = start;
    for (int &parameterIndex : parameterIndices) {
        parameterIndex = i <= end ? i : -1;
        i++;
    }

    SerialUSB.println("Active parameters:");

    for (int index : parameterIndices) {
        if (index >= 0) {
            SynthParameter param = section->getParameters()[index];
            SerialUSB.print(" - ");
            SerialUSB.print(param.getName().c_str());
            SerialUSB.print(" (");
            SerialUSB.print(param.getNumber(0));
            SerialUSB.println(")");
        }
    }

    showActivePage();
}

void ParameterController::showActivePage() {
    if (section == nullptr) {
        upButton->setLED(false);
        downButton->setLED(false);
        return;
    };

    int numberOfPages = section->getNumberOfPages();
    upButton->setLED(numberOfPages > 1 && activePage > 1);
    downButton->setLED(numberOfPages > 1 && activePage < numberOfPages);
}




