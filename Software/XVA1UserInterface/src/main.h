//
// Created by André Mathlener on 05/04/2021.
//

#ifndef XVA1USERINTERFACE_MAIN_H
#define XVA1USERINTERFACE_MAIN_H

/* function prototypes */

void handleMainEncoder(bool clockwise);

void handleParameterChange(SynthParameter *parameter, bool clockwise, int speed);

void displayTwinParameters(SynthParameter *parameter1, SynthParameter *parameter2, int displayNumber);

void displayTwinParameters(const char *title1, char *value1, const char *title2, char *value2, int displayNumber);

void initOLEDDisplays();

void pollAllMCPs();

void readButtons();

void selectPatchOnSynth(int number);

void getPatchDataFromSynth();

void displayPatchInfo();

void initButtons();

void setParameter(int number, int value);

#endif //XVA1USERINTERFACE_MAIN_H
