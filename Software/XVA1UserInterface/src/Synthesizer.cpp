//
// Created by André Mathlener on 07/04/2021.
//

#include "Synthesizer.h"
#include <HardwareSerial.h>

HardwareSerial SynthSerial(0);

void Synthesizer::selectPatch(int number) {

    int synthPatchNumber = number - 1;

    Serial.print("Selecting patch #");
    Serial.print(synthPatchNumber);
    Serial.print(" on Synth...");

    SynthSerial.write('r'); // 'r' = Read program
    SynthSerial.write(synthPatchNumber);


    int read_status;
    int bytesRead = 0;
    int retry = 0;
    while (bytesRead == 0 && retry != 100) {
        if (SynthSerial.available()) {
            read_status = SynthSerial.read();
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
    SynthSerial.write('d'); // 'd' = Display program

    Serial.println("Reading patch data from Synth...");

    byte rxBuffer[512];
    int bytesRead = 0;
    int retry = 0;
    while (bytesRead != 512 && retry != 100) {
        if (SynthSerial.available()) {
            byte b = SynthSerial.read();
            rxBuffer[bytesRead] = b;
            bytesRead++;
            retry = 0;
        } else {
            retry++;
            delay(10);
        }
    }

    SynthSerial.flush();
    memcpy(currentPatchData, rxBuffer, 512);

    setCurrentPatchName();
}

void Synthesizer::setCurrentPatchName() {
    string patchName = "";

    for (int i = 480; i <= 504; i++) {
        patchName += (char) currentPatchData[i];
    }
    currentPatchName = patchName;

    Serial.print("Patch name: ");
    Serial.println(patchName.c_str());
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
    SynthSerial.write('s'); // 's' = Set Parameter

    if (number > 255) {
        // Parameters above 255 have a two-byte format: b1 = 255, b2 = x-256
        SynthSerial.write(255);
        SynthSerial.write(number - 256);
        SynthSerial.write(value);
    } else {
        SynthSerial.write(number);
        SynthSerial.write(value);
    }

    currentPatchData[number] = value;

    if (number >= 480 && number <= 504) {
        setCurrentPatchName();
    }
}

void Synthesizer::begin() {
    // Configure SynthSerial on pins TX=D6 and RX=D7 (-1, -1 means use the default)
    SynthSerial.begin(500000, SERIAL_8N1, -1, -1);
}

Envelope Synthesizer::getEnvelopeValues(Envelope &envelope) {
    Envelope returnEnvelope = Envelope();

    for (int i = 0; i < 6; ++i) {
        returnEnvelope.level[i] = getParameter(envelope.level[i]);
        returnEnvelope.rate[i] = getParameter(envelope.rate[i]);
    }

    return returnEnvelope;
}


