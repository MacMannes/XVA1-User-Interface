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
 * 1. Voice
 */

Section voiceSection = Section(
        "Voice",
        {
                SynthParameterBuilder("Transpose")
                        .type(CENTER_128)
                        .number(241)
                        .build(),
                SynthParameterBuilder("Bend Up")
                        .number(242)
                        .build(),
                SynthParameterBuilder("Bend Down")
                        .number(243)
                        .build(),
        }
);

/**
 * 2. Mixer
 */

Section mixerSection = Section(
        "Mixer",
        {
                SynthParameterBuilder("OSC 1 Volume")
                        .number(27)
                        .build(),
                SynthParameterBuilder("OSC 2 Volume")
                        .number(28)
                        .build(),
                SynthParameterBuilder("OSC 3 Volume")
                        .number(29)
                        .build(),
                SynthParameterBuilder("OSC 4 Volume")
                        .number(30)
                        .build(),
                SynthParameterBuilder("OSC 1 Level L")
                        .number(31)
                        .build(),
                SynthParameterBuilder("OSC 2 Level L")
                        .number(33)
                        .build(),
                SynthParameterBuilder("OSC 3 Level L")
                        .number(35)
                        .build(),
                SynthParameterBuilder("OSC 4 Level L")
                        .number(37)
                        .build(),
                SynthParameterBuilder("OSC 1 Level R")
                        .number(32)
                        .build(),
                SynthParameterBuilder("OSC 2 Level R")
                        .number(34)
                        .build(),
                SynthParameterBuilder("OSC 3 Level R")
                        .number(36)
                        .build(),
                SynthParameterBuilder("OSC 4 Level R")
                        .number(38)
                        .build(),
        }
);

/**
 * 3. Effects
 */

Section effectsSection = Section(
        "Effects",
        {
                Section(
                        "Chorus/Flanger",
                        {
                                SynthParameterBuilder("DRY")
                                        .number(360)
                                        .build(),
                                SynthParameterBuilder("WET")
                                        .number(351)
                                        .build(),
                        }

                ),
                Section(
                        "Phaser",
                        {
                                SynthParameterBuilder("DRY")
                                        .number(310)
                                        .build(),
                                SynthParameterBuilder("WET")
                                        .number(311)
                                        .build(),
                        }

                ),
                Section(
                        "Delay",
                        {
                                SynthParameterBuilder("DRY")
                                        .number(300)
                                        .build(),
                                SynthParameterBuilder("WET")
                                        .number(301)
                                        .build(),
                        }

                )
        }
);
/**
 * 4. ARP
 */

Section arpSection = Section(
        "ARP",
        {
                SynthParameterBuilder("MODE")
                        .number(450)
                        .build(),
                SynthParameterBuilder("Temp")
                        .number(451)
                        .min(44)
                        .build(),
        }
);

/**
 * 5. Oscillators
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

/**
 * 6. Envelopes
 */

Section envelopeSection = Section(
        "Envelopes",
        {"PITCH", "CUTOFF", "AMP"},
        {
                SynthParameterBuilder("L0")
                        .numbers({80, 81, 82})
                        .build()
        }
);

/**
 * 7. LFOs
 */

Section lfoSection = Section(
        "LFO",
        {"LFO1", "LFO2"},
        {
                SynthParameterBuilder("Wave")
                        .numbers({160, 170})
                        .max(9)
                        .build()
        }
);

/**
 * 8. Filter
 */

Section filterSection = Section(
        "Filter",
        {
                SynthParameterBuilder("Cutoff 1")
                        .number(72)
                        .build(),

                SynthParameterBuilder("Resonance 1")
                        .number(77)
                        .build(),

                SynthParameterBuilder("Cutoff 2")
                        .number(78)
                        .build(),

                SynthParameterBuilder("Resonance 2")
                        .number(79)
                        .build(),

                SynthParameterBuilder("Type")
                        .number(7)
                        .max(21)
                        .build()
        }
);

/**
 * 9. Patch
 */

/**
 * 10. External Controls
 */

/**
 * 11. Performance Controls
 */

/**
 * Sequencer
 */

Section *shortcutSections[] = {
        &voiceSection, &mixerSection, &effectsSection, &arpSection,
        &oscillatorSection, &envelopeSection, &lfoSection, &filterSection
};

#endif //XVA1USERINTERFACE_XVA1SYNTHPARAMETERS_H
