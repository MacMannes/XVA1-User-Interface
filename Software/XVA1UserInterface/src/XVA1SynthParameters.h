//
// Created by André Mathlener on 05/04/2021.
//

#ifndef XVA1USERINTERFACE_XVA1SYNTHPARAMETERS_H
#define XVA1USERINTERFACE_XVA1SYNTHPARAMETERS_H

#include "Section.h"

SynthParameter param1 = SynthParameterBuilder("Sequencer")
        .number(428)
        .max(1)
        .descriptions({"OFF", "ON"})
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


Section oscillatorSection = Section(
        "Oscillators",
        {"Oscillator 1", "Oscillator 2", "Oscillator 3", "Oscillator 4"},
        {
                SynthParameterBuilder("On or Off")
                        .numbers({1, 2, 3, 4})
                        .max(1)
                        .descriptions({"OFF", "ON"})
                        .build(),

                SynthParameterBuilder("Waveform")
                        .numbers({11, 12, 13, 14})
                        .max(8)
                        .descriptions(
                                {"Saw up", "Saw down", "Square", "Triangle", "Sine", "Noise", "Sawstack x3 (stereo)",
                                 "Sawstack x7 (mono)", "Sawstack x7 (stereo)"})
                        .build(),

                SynthParameterBuilder("Phase")
                        .numbers({7, 8, 9, 10})
                        .max(3)
                        .descriptions({"0 deg", "90 deg", "180 deg", "270 deg"})
                        .build(),
                SynthParameterBuilder("Pulse Width")
                        .type(CENTER_128)
                        .numbers({15, 16, 17, 18})
                        .build(),

                SynthParameterBuilder("Transpose")
                        .type(CENTER_128)
                        .numbers({19, 20, 21, 22})
                        .build(),

                SynthParameterBuilder("Detune")
                        .type(CENTER_128)
                        .numbers({23, 24, 25, 26})
                        .build(),

                SynthParameterBuilder("Sawstack Detune")
                        .numbers({285, 286, 287, 288})
                        .build(),

                SynthParameterBuilder("Drift")
                        .numbers({260, 261, 262, 263})
                        .build(),

                SynthParameterBuilder("Key breakpoint")
                        .numbers({43, 44, 45, 46})
                        .build(),

                SynthParameterBuilder("Key L depth")
                        .numbers({47, 48, 49, 50})
                        .build(),

                SynthParameterBuilder("Key R depth")
                        .numbers({51, 52, 53, 54})
                        .build(),

                SynthParameterBuilder("Key L curve")
                        .numbers({55, 56, 57, 58})
                        .build(),

                SynthParameterBuilder("Key R curve")
                        .numbers({59, 60, 61, 62})
                        .build(),

                SynthParameterBuilder("PMS")
                        .numbers({63, 64, 65, 66})
                        .build(),

                SynthParameterBuilder("AMS")
                        .numbers({67, 66, 67, 68})
                        .build()
        }
);

Section *shortcutSections[] = {
        &oscillatorSection
};

#endif //XVA1USERINTERFACE_XVA1SYNTHPARAMETERS_H
