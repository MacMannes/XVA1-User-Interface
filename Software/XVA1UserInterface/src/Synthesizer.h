//
// Created by André Mathlener on 07/04/2021.
//

#ifndef XVA1USERINTERFACE_SYNTHESIZER_H
#define XVA1USERINTERFACE_SYNTHESIZER_H

#include <string>
#include <Arduino.h>

using namespace std;

class Synthesizer {
private:
    int currentPatchNumber = 1;
    string currentPatchName = "";
    byte currentPatchData[512] = {};

public:
    void begin();

    void selectPatch(int number);

    void loadPatchData();

    int getPatchNumber() const;

    const string &getPatchName() const;

    byte getParameter(int number) const;

    void setParameter(int number, int value);
};


#endif //XVA1USERINTERFACE_SYNTHESIZER_H
