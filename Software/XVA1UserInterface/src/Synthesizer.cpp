//
// Created by André Mathlener on 07/04/2021.
//

#include "Synthesizer.h"

#include <HardwareSerial.h>

#include "Debug.h"

HardwareSerial SynthSerial(1);  // UART1 — keeps UART0 free for Serial (debug)

void Synthesizer::selectPatch(int number) {
    int synthPatchNumber = number - 1;

    LOG("Selecting patch #");
    LOG(synthPatchNumber);
    LOG(" on Synth...");

    SynthSerial.write('r');  // 'r' = Read program
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

    LOG("Status=");
    LOGLN(read_status, DEC);

    loadPatchData();
    currentPatchNumber = number;
}

void Synthesizer::loadPatchData() {
    SynthSerial.write('d');  // 'd' = Display program

    LOGLN("Reading patch data from Synth...");

    byte rxBuffer [512];
    int bytesRead = 0;
    int retry = 0;
    while (bytesRead != 512 && retry != 100) {
        if (SynthSerial.available()) {
            byte b = SynthSerial.read();
            rxBuffer [bytesRead] = b;
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
        patchName += (char)currentPatchData [i];
    }
    currentPatchName = patchName;

    LOG("Patch name: ");
    LOGLN(patchName.c_str());
}

int Synthesizer::getPatchNumber() const {
    return currentPatchNumber;
}

const string& Synthesizer::getPatchName() const {
    return currentPatchName;
}

byte Synthesizer::getParameter(int number) const {
    return currentPatchData [number];
}

void Synthesizer::setParameter(int number, int value) {
    SynthSerial.write('s');  // 's' = Set Parameter

    if (number > 255) {
        // Parameters above 255 have a two-byte format: b1 = 255, b2 = x-256
        SynthSerial.write(255);
        SynthSerial.write(number - 256);
        SynthSerial.write(value);
    } else {
        SynthSerial.write(number);
        SynthSerial.write(value);
    }

    // Wait until all bytes are physically transmitted before returning.
    // Several parameter numbers (e.g. 116 = 't', 86 = 'V') coincide with
    // destructive synth commands. If the UART TX buffer overflows and the
    // leading 's' byte is dropped, the synth interprets the parameter number
    // as a command, potentially triggering a flash erase/write.
    // flush() costs ~60 µs at 500 kbps — imperceptible to the user.
    SynthSerial.flush();

    currentPatchData [number] = value;

    if (number >= 480 && number <= 504) {
        setCurrentPatchName();
    }
}

void Synthesizer::begin() {
    // Configure SynthSerial on UART1, routed to physical pins D6 (GPIO43 = TX)
    // and D7 (GPIO44 = RX) The ESP32-S3 GPIO matrix allows UART1 to be mapped
    // to any pins, including GPIO43/44.
    SynthSerial.begin(
        500000, SERIAL_8N1, 44, 43
    );  // RX=GPIO44(D7), TX=GPIO43(D6)
}

Envelope Synthesizer::getEnvelopeValues(Envelope& envelope) {
    Envelope returnEnvelope = Envelope();

    for (int i = 0; i < 6; ++i) {
        returnEnvelope.level [i] = getParameter(envelope.level [i]);
        returnEnvelope.rate [i] = getParameter(envelope.rate [i]);
    }

    return returnEnvelope;
}
