//
// Created by André Mathlener on 05/04/2021.
//

#ifndef XVA1USERINTERFACE_XVA1SYNTHPARAMETERS_H
#define XVA1USERINTERFACE_XVA1SYNTHPARAMETERS_H

SynthParameter param1 = SynthParameterBuilder("Sequencer")
        .number(428)
        .max(1)
        .descriptions({ "OFF", "ON" })
        .build();
SynthParameter param2 = SynthParameterBuilder("Cutoff")
        .number(72)
        .build();
SynthParameter param3 = SynthParameterBuilder("PerfCtl1")
        .performanceControlType(400, 401)
        .build();
SynthParameter param4 = SynthParameterBuilder("PerfCtl2")
        .performanceControlType(402, 403)
        .build();

/**
 * Oscillators
 */

SynthParameter oscillatorOnOrOff = SynthParameterBuilder("On or Off")
        .numbers({ 1, 2, 3, 4 })
        .max(1)
        .descriptions({ "OFF", "ON" })
        .build();


SynthParameter oscillatorWaveform = SynthParameterBuilder("Waveform")
        .numbers({ 11, 12, 13, 14 })
        .max(8)
        .descriptions({ "Saw up", "Saw down", "Square", "Triangle", "Sine", "Noise", "Sawstack x3 (stereo)", "Sawstack x7 (mono)", "Sawstack x7 (stereo)" })
        .build();

#endif //XVA1USERINTERFACE_XVA1SYNTHPARAMETERS_H
