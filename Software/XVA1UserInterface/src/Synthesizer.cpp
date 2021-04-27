//
// Created by André Mathlener on 07/04/2021.
//

#include "Synthesizer.h"

void Synthesizer::selectPatch(int number) {
    int synthPatchNumber = number - 1;

    Serial.print("Selecting patch #");
    Serial.print(synthPatchNumber);
    Serial.print(" on Synth...");

    Serial2.write('r'); // 'r' = Read program
    Serial2.write(synthPatchNumber);


    int read_status;
    int bytesRead = 0;
    int retry = 0;
    while (bytesRead == 0 && retry != 100) {
        if (Serial2.available()) {
            read_status = Serial2.read();
            bytesRead++;
            retry = 0;
        } else {
            retry++;
            delay(10);
        }
    }

    Serial.print("Status=");
    Serial.println(read_status, DEC);

    loadPatchData();
    currentPatchNumber = number;
}

void Synthesizer::loadPatchData() {
    Serial2.write('d'); // 'd' = Display program

    Serial.println("Reading patch data from Synth...");

    byte rxBuffer[512];
    int bytesRead = 0;
    int retry = 0;
    while (bytesRead != 512 && retry != 100) {
        if (Serial2.available()) {
            byte b = Serial2.read();
            rxBuffer[bytesRead] = b;
            bytesRead++;
            retry = 0;
        } else {
            retry++;
            delay(10);
        }
    }

    Serial.println();

    string patchName = "";

    for (int i = 480; i < 505; i++) {
        patchName += (char) rxBuffer[i];
    }

    Serial.print("Patch name: ");
    Serial.println(patchName.c_str());
    Serial.println();

    Serial2.flush();

    memcpy(currentPatchData, rxBuffer, 512);
    currentPatchName = patchName;
}

int Synthesizer::getPatchNumber() const {
    return currentPatchNumber;
}

const string &Synthesizer::getPatchName() const {
    return currentPatchName;
}

byte Synthesizer::getParameter(int number) const {
    return currentPatchData[number];
}

void Synthesizer::setParameter(int number, int value) {
    Serial2.write('s'); // 's' = Set Parameter

    if (number > 255) {
        // Parameters above 255 have a two-byte format: b1 = 255, b2 = x-256
        Serial2.write(255);
        Serial2.write(number - 256);
        Serial2.write(value);
    } else {
        Serial2.write(number);
        Serial2.write(value);
    }

    currentPatchData[number] = value;
}

void Synthesizer::begin() {
    Serial2.begin(500000, SERIAL_8N1, 16, 17); // XVA1 Serial

}


