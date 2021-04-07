//
// Created by André Mathlener on 07/04/2021.
//

#include "Synthesizer.h"

void Synthesizer::selectPatch(int number) {
    int synthPatchNumber = number - 1;

    SerialUSB.print("Selecting patch #");
    SerialUSB.print(synthPatchNumber);
    SerialUSB.print(" on Synth...");

    Serial1.write('r'); // 'r' = Read program
    Serial1.write(synthPatchNumber);


    int read_status;
    int bytesRead = 0;
    int retry = 0;
    while (bytesRead == 0 && retry != 100) {
        if (Serial1.available()) {
            read_status = Serial1.read();
            bytesRead++;
            retry = 0;
        } else {
            retry++;
            delay(10);
        }
    }

    SerialUSB.print("Status=");
    SerialUSB.println(read_status, DEC);

    loadPatchData();
    currentPatchNumber = number;
}

void Synthesizer::loadPatchData() {
    Serial1.write('d'); // 'd' = Display program

    SerialUSB.println("Reading patch data from Synth...");

    byte rxBuffer[512];
    int bytesRead = 0;
    int retry = 0;
    while (bytesRead != 512 && retry != 100) {
        if (Serial1.available()) {
            byte b = Serial1.read();
            rxBuffer[bytesRead] = b;
            bytesRead++;
            retry = 0;
        } else {
            retry++;
            delay(10);
        }
    }

    SerialUSB.println();

    string patchName = "";

    for (int i = 480; i < 505; i++) {
        patchName += (char) rxBuffer[i];
    }

    SerialUSB.print("Patch name: ");
    SerialUSB.println(patchName.c_str());
    SerialUSB.println();

    Serial1.flush();

    memcpy(currentPatchData, rxBuffer, 512);
    currentPatchName = patchName;
}

int Synthesizer::getPatchNumber() const {
    return currentPatchNumber;
}

const string &Synthesizer::getPatchName() const {
    return currentPatchName;
}

const byte *Synthesizer::getPatchData() const {
    return currentPatchData;
}

const byte Synthesizer::getParameter(int number) const {
    return currentPatchData[number];
}

void Synthesizer::setParameter(int number, int value) {
    Serial1.write('s'); // 's' = Set Parameter

    if (number > 255) {
        // Parameters above 255 have a two-byte format: b1 = 255, b2 = x-256
        Serial1.write(255);
        Serial1.write(number - 256);
        Serial1.write(value);
    } else {
        Serial1.write(number);
        Serial1.write(value);
    }

    currentPatchData[number] = value;
}


