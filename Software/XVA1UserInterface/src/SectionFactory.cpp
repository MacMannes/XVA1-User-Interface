//
// Created by André Mathlener on 16/04/2021.
//

#include "SectionFactory.h"
#include "SynthParameter.h"

Section SectionFactory::createDefaultSection() {
    return Section("Default")
            .parameters(
                    {
                            SynthParameter("Cutoff")
                                    .number(72),

                            SynthParameter("Resonance")
                                    .number(77),

                            SynthParameter("Sequencer")
                                    .number(428)
                                    .max(1)
                                    .descriptions({"OFF", "ON"})
                    }
            );
}

Section SectionFactory::createVoiceSection() {
    return Section("Voice")
            .parameters(
                    {
                            SynthParameter("Transpose")
                                    .type(CENTER_128)
                                    .number(241),
                            SynthParameter("Bend Up")
                                    .number(242),
                            SynthParameter("Bend Down")
                                    .number(243)

                    }
            );
}

Section SectionFactory::createMixerSection() {
    return Section("Mixer")
            .subSections(
                    {
                            Section("Output")
                                    .parameters(
                                            {
                                                    SynthParameter("Volume")
                                                            .number(509),
                                                    SynthParameter(""),
                                                    SynthParameter("Gain Pre-FX")
                                                            .number(510)
                                                            .max(4)
                                                            .descriptions(
                                                                    {"0 dB", "+6 dB", "+12 dB", "+18 dB"}),
                                                    SynthParameter(""),
                                                    SynthParameter("Gain Post-FX")
                                                            .number(511)
                                                            .max(4)
                                                            .descriptions(
                                                                    {"0 dB", "+6 dB", "+12 dB", "+18 dB"})
                                            }
                                    ),
                            Section("Oscillator levels")
                                    .parameters(
                                            {
                                                    SynthParameter("OSC 1")
                                                            .number(27),
                                                    SynthParameter(""),
                                                    SynthParameter("OSC 2")
                                                            .number(28),
                                                    SynthParameter(""),
                                                    SynthParameter("OSC 3")
                                                            .number(29),
                                                    SynthParameter(""),
                                                    SynthParameter("OSC 4")
                                                            .number(30)
                                            }
                                    ),
                            Section("Oscillator Panning")
                                    .parameters(
                                            {
                                                    SynthParameter("OSC 1 Level L")
                                                            .number(31),
                                                    SynthParameter("OSC 1 Level R")
                                                            .number(32),
                                                    SynthParameter("OSC 2 Level L")
                                                            .number(33),
                                                    SynthParameter("OSC 2 Level R")
                                                            .number(34),
                                                    SynthParameter("OSC 3 Level L")
                                                            .number(35),
                                                    SynthParameter("OSC 3 Level R")
                                                            .number(36),
                                                    SynthParameter("OSC 4 Level L")
                                                            .number(37),
                                                    SynthParameter("OSC 4 Level R")
                                                            .number(38)
                                            }
                                    )
                    }
            );
}

Section SectionFactory::createEffectsSection() {
    return Section("Effects")
            .subSections(
                    {
                            Section("Bandwidth limit")
                                    .parameters(
                                            {
                                                    SynthParameter("Bandwidth")
                                                            .number(340)
                                                            .max(7)
                                                            .descriptions(
                                                                    {
                                                                            "No filter", "20 kHz", "18 kHz",
                                                                            "16 kHz", "14 kHz",
                                                                            "12 kHz", "10 kHz", "8 kHz"
                                                                    }
                                                            )
                                            }
                                    ),
                            Section("Distortion")
                                    .parameters(
                                            {
                                                    SynthParameter("On or Off")
                                                            .number(340)
                                                            .max(1)
                                                            .descriptions({"OFF", "ON"}),
                                                    SynthParameter("Type")
                                                            .number(354)
                                                            .max(3)
                                                            .descriptions(
                                                                    {"Hard clipping", "Soft clipping", "Tube 12AX",
                                                                     "Tube DSL"}),
                                                    SynthParameter("Gain PRE")
                                                            .number(354),
                                                    SynthParameter("Gain POST")
                                                            .number(354),
                                                    SynthParameter("Filter POST")
                                                            .number(340)
                                                            .max(7)
                                                            .descriptions(
                                                                    {
                                                                            "No filter", "20 kHz", "18 kHz", "16 kHz",
                                                                            "14 kHz",
                                                                            "12 kHz", "10 kHz", "8 kHz"
                                                                    }
                                                            )
                                            }
                                    ),
                            Section("Chorus/Flanger")
                                    .parameters(
                                            {
                                                    SynthParameter("DRY")
                                                            .number(360),
                                                    SynthParameter("WET")
                                                            .number(351)

                                            }
                                    ),
                            Section("Phaser")
                                    .parameters(
                                            {
                                                    SynthParameter("DRY")
                                                            .number(310),
                                                    SynthParameter("WET")
                                                            .number(311)

                                            }
                                    ),
                            Section("Delay")
                                    .parameters(
                                            {
                                                    SynthParameter("DRY")
                                                            .number(300),
                                                    SynthParameter("WET")
                                                            .number(301)
                                            }
                                    )
                    }
            );
}

Section SectionFactory::createArpSection() {
    return Section("ARP")
            .parameters(
                    {
                            SynthParameter("MODE")
                                    .number(450),
                            SynthParameter("Temp")
                                    .number(451)
                                    .min(44)

                    }
            );
}

Section SectionFactory::createOscillatorSection() {
    return Section("Oscillators")
            .virtualSubSectionTitles({"Oscillator 1", "Oscillator 2", "Oscillator 3", "Oscillator 4"})
            .parameters(
                    {
                            SynthParameter("On or Off")
                                    .numbers({1, 2, 3, 4})
                                    .max(1)
                                    .descriptions({"OFF", "ON"}),

                            SynthParameter("Mode")
                                    .type(BITWISE)
                                    .number(6)
                                    .bitNumbers({0, 1, 2, 3})
                                    .descriptions({"KeyTrack", "FixedPitch"}),

                            SynthParameter("Sync")
                                    .type(BITWISE)
                                    .number(5)
                                    .bitNumbers({0, 1, 2, 3})
                                    .descriptions({"Free running", "Restart on Key-ON"}),

                            SynthParameter("Waveform")
                                    .numbers({11, 12, 13, 14})
                                    .max(8)
                                    .descriptions(
                                            {"Saw up", "Saw down", "Square", "Triangle", "Sine",
                                             "Noise", "Sawstack x3 (stereo)",
                                             "Sawstack x7 (mono)", "Sawstack x7 (stereo)"}),

                            SynthParameter("Phase")
                                    .numbers({7, 8, 9, 10})
                                    .max(3)
                                    .descriptions({"0 deg", "90 deg", "180 deg", "270 deg"}),

                            SynthParameter("Pulse Width")
                                    .type(CENTER_128)
                                    .numbers({15, 16, 17, 18}),

                            SynthParameter("Transpose")
                                    .type(CENTER_128)
                                    .numbers({19, 20, 21, 22}),

                            SynthParameter("Detune")
                                    .type(CENTER_128)
                                    .numbers({23, 24, 25, 26}),

                            SynthParameter("Sawstack Detune")
                                    .numbers({285, 286, 287, 288}),

                            SynthParameter("Drift")
                                    .numbers({260, 261, 262, 263}),

                            SynthParameter("Key breakpoint")
                                    .numbers({43, 44, 45, 46}),

                            SynthParameter("Key L depth")
                                    .numbers({47, 48, 49, 50}),

                            SynthParameter("Key R depth")
                                    .numbers({51, 52, 53, 54}),

                            SynthParameter("Key L curve")
                                    .numbers({55, 56, 57, 58}),

                            SynthParameter("Key R curve")
                                    .numbers({59, 60, 61, 62}),

                            SynthParameter("PMS")
                                    .numbers({63, 64, 65, 66}),

                            SynthParameter("AMS")
                                    .numbers({67, 66, 67, 68})
                    }
            );
}

Section SectionFactory::createEnvelopeSection() {
    return Section("Envelopes")
            .virtualSubSectionTitles({"PITCH", "CUTOFF", "AMP"})
            .parameters(
                    {
                            SynthParameter("L0 - Start")
                                    .numbers({80, 81, 82}),
                            SynthParameter("L4 - Release 1")
                                    .numbers({100, 101, 102}),
                            SynthParameter("L1 - Attack")
                                    .numbers({85, 86, 88}),
                            SynthParameter("L5 - Release 2")
                                    .numbers({105, 106, 107}),
                            SynthParameter("L2 - Decay")
                                    .numbers({90, 91, 92}),
                            SynthParameter(""),
                            SynthParameter("L3 - Sustain")
                                    .numbers({95, 96, 97}),
                            SynthParameter("Delay")
                                    .numbers({110, 111, 112}),
                            SynthParameter("R1 - Attack")
                                    .numbers({115, 116, 117}),
                            SynthParameter("R5 - Release 2")
                                    .numbers({135, 136, 137}),
                            SynthParameter("R2 - Decay")
                                    .numbers({120, 121, 122}),
                            SynthParameter(""),
                            SynthParameter("R3 - Sustain")
                                    .numbers({125, 126, 127}),
                            SynthParameter(""),
                            SynthParameter("R4 - Release 1")
                                    .numbers({130, 131, 132}),
                            SynthParameter(""),

                            SynthParameter("EG Loop")
                                    .type(BITWISE)
                                    .number(145)
                                    .bitNumbers({0, 1, 6})
                                    .descriptions({"Normal", "Loop"}),
                            SynthParameter(""),
                            SynthParameter("EG Loop Segment")
                                    .type(BITWISE)
                                    .number(146)
                                    .bitNumbers({0, 1, 6})
                                    .descriptions({"L0 - Attack", "L5 - Decay"}),
                            SynthParameter(""),
                            SynthParameter("EG Restart from")
                                    .type(BITWISE)
                                    .number(147)
                                    .bitNumbers({0, 1, 6})
                                    .descriptions({"L5 - Decay", "L0 - Start"}),
                            SynthParameter(""),
                            SynthParameter("Range")
                                    .numbers({148, -1, -1})
                                    .max(10),
                            SynthParameter("Velocity")
                                    .numbers({149, -1, -1})
                                    .max(10)

                    }
            );
}

Section SectionFactory::createLFOSection() {
    return Section("LFO")
            .subSections(
                    {
                            Section("LFO1")
                                    .parameters(
                                            {
                                                    SynthParameter("Wave")
                                                            .number(160)
                                                            .max(9)
                                                            .descriptions(
                                                                    {
                                                                            "Triangle", "Square", "Saw Up",
                                                                            "Saw Down", "Sine",
                                                                            "Sin( x ) + Sin( 2x )",
                                                                            "Sin( x ) + Sin( 3x )",
                                                                            "Sin( x ) ^ 3",
                                                                            "Guitar", "S & H"
                                                                    }
                                                            ),
                                                    SynthParameter("Range")
                                                            .number(166),
                                                    SynthParameter("Speed")
                                                            .number(161),
                                                    SynthParameter("Sync")
                                                            .number(162)
                                                            .descriptions(
                                                                    {
                                                                            "Single, Free running",
                                                                            "Single, Key sync",
                                                                            "Multi, Free running",
                                                                            "Multi, Key sync"
                                                                    }
                                                            ),
                                                    SynthParameter("Fade")
                                                            .number(163),
                                                    SynthParameter("Depth Pitch")
                                                            .number(164),
                                                    SynthParameter("AMP Pitch")
                                                            .number(165)
                                            }),
                            Section("LFO2")
                                    .parameters(
                                            {
                                                    SynthParameter("Wave")
                                                            .number(170)
                                                            .max(9)
                                                            .descriptions(
                                                                    {
                                                                            "Triangle", "Square", "Saw Up",
                                                                            "Saw Down", "Sine",
                                                                            "Sin( x ) + Sin( 2x )",
                                                                            "Sin( x ) + Sin( 3x )",
                                                                            "Sin( x ) ^ 3",
                                                                            "Guitar", "S & H"
                                                                    }),
                                                    SynthParameter("Range")
                                                            .number(176),
                                                    SynthParameter("Speed")
                                                            .number(171),
                                                    SynthParameter("Sync")
                                                            .number(172)
                                                            .descriptions(
                                                                    {
                                                                            "Single, Free running",
                                                                            "Single, Key sync",
                                                                            "Multi, Free running",
                                                                            "Multi, Key sync"
                                                                    }
                                                            ),
                                                    SynthParameter("Fade")
                                                            .number(173),
                                                    SynthParameter("Depth Pitch")
                                                            .number(174),
                                                    SynthParameter("AMP Pitch")
                                                            .number(175)
                                            })

                    }
            );
}

Section SectionFactory::createFilterSection() {
    return Section("Filters")
            .subSections(
                    {
                            Section("Filter 1")
                                    .parameters(
                                            {

                                                    SynthParameter("Cutoff")
                                                            .number(72),

                                                    SynthParameter("Resonance")
                                                            .number(77)
                                            }
                                    ),
                            Section("Filter 2")
                                    .parameters(
                                            {
                                                    SynthParameter("Cutoff")
                                                            .number(78),

                                                    SynthParameter("Resonance")
                                                            .number(79),
                                            }
                                    ),
                            Section("Settings")
                                    .parameters(
                                            {

                                                    SynthParameter("Type")
                                                            .number(71)
                                                            .max(21)
                                                            .descriptions(
                                                                    {
                                                                            "Bypass", "LPF 1P", "LPF 2P",
                                                                            "LPF 3P", "LPF 4P",
                                                                            "HPF 1P",
                                                                            "HPF 2P", "HPF 3P", "HPF 4P",
                                                                            "BPF 2P", "BPF 4P",
                                                                            "BRF 2P",
                                                                            "BRF 4P", "LP -> LP", "LP -> BP",
                                                                            "LP -> HP", "LP // LP",
                                                                            "LP // BP", "LP // HP",
                                                                            "BP // BP", "BP // HP", "HP // HP"
                                                                    }
                                                            ),
                                                    SynthParameter("Velocity")
                                                            .type(CENTER_128)
                                                            .number(73),
                                                    SynthParameter("KBD Track")
                                                            .type(CENTER_128)
                                                            .number(74),
                                                    SynthParameter("EG depth")
                                                            .type(CENTER_128)
                                                            .number(75),
                                                    SynthParameter("EG Velocity")
                                                            .type(CENTER_128)
                                                            .number(76),
                                                    SynthParameter("Velocity RESO")
                                                            .type(CENTER_128)
                                                            .number(276),
                                                    SynthParameter("KBD Track RESO")
                                                            .type(CENTER_128)
                                                            .number(277),
                                                    SynthParameter("Drive")
                                                            .number(275)
                                                            .max(7),
                                                    SynthParameter("Routing")
                                                            .number(278)
                                                            .max(1)
                                                            .descriptions({"Standard", "LR Mode"})
                                            }
                                    )
                    }
            );
}

Section SectionFactory::createPatchSection() {
    return Section("Patch")
            .parameters(
                    {
                            SynthParameter("")
                    }
            );
}

Section SectionFactory::createExternalControlsSection() {
    return Section("External Ctrls")
            .subSections(
                    {
                            Section("Pitch")
                                    .parameters(
                                            {
                                                    SynthParameter("Aftertouch")
                                                            .number(200)
                                                            .type(CENTER_128),
                                                    SynthParameter("Breath")
                                                            .number(201)
                                                            .type(CENTER_128),
                                                    SynthParameter("Foot")
                                                            .number(202)
                                                            .type(CENTER_128),
                                                    SynthParameter("Temperature")
                                                            .number(220)
                                                            .type(CENTER_128),
                                                    SynthParameter("CV-1")
                                                            .number(221)
                                                            .type(CENTER_128),
                                                    SynthParameter("CV-2")
                                                            .number(222)
                                                            .type(CENTER_128),
                                                    SynthParameter("Random")
                                                            .number(203)
                                            }
                                    ),
                            Section("Pulse Width")
                                    .parameters(
                                            {
                                                    SynthParameter("Aftertouch")
                                                            .number(204)
                                                            .type(CENTER_128),
                                                    SynthParameter("Wheel")
                                                            .number(205)
                                                            .type(CENTER_128),
                                                    SynthParameter("Breath")
                                                            .number(206)
                                                            .type(CENTER_128),
                                                    SynthParameter("Foot")
                                                            .number(207)
                                                            .type(CENTER_128),
                                                    SynthParameter("Temperature")
                                                            .number(223)
                                                            .type(CENTER_128),
                                                    SynthParameter("CV-1")
                                                            .number(224)
                                                            .type(CENTER_128),
                                                    SynthParameter("CV-2")
                                                            .number(225)
                                                            .type(CENTER_128)}
                                    ),
                            Section("Cutoff")
                                    .parameters(
                                            {
                                                    SynthParameter("Aftertouch")
                                                            .number(208)
                                                            .type(CENTER_128),
                                                    SynthParameter("Wheel")
                                                            .number(209)
                                                            .type(CENTER_128),
                                                    SynthParameter("Breath")
                                                            .number(210)
                                                            .type(CENTER_128),
                                                    SynthParameter("Foot")
                                                            .number(211)
                                                            .type(CENTER_128),
                                                    SynthParameter("Temperature")
                                                            .number(226)
                                                            .type(CENTER_128),
                                                    SynthParameter("CV-1")
                                                            .number(227)
                                                            .type(CENTER_128),
                                                    SynthParameter("CV-2")
                                                            .number(228)
                                                            .type(CENTER_128)}
                                    ),
                            Section("Volume")
                                    .parameters(
                                            {
                                                    SynthParameter("Aftertouch")
                                                            .number(212)
                                                            .type(CENTER_128),
                                                    SynthParameter("Wheel")
                                                            .number(213)
                                                            .type(CENTER_128),
                                                    SynthParameter("Breath")
                                                            .number(214)
                                                            .type(CENTER_128),
                                                    SynthParameter("Foot")
                                                            .number(215)
                                                            .type(CENTER_128),
                                                    SynthParameter("Temperature")
                                                            .number(228)
                                                            .type(CENTER_128),
                                                    SynthParameter("CV-1")
                                                            .number(230)
                                                            .type(CENTER_128),
                                                    SynthParameter("CV-2")
                                                            .number(231)
                                                            .type(CENTER_128),}
                                    ),
                            Section("Pitch LFO")
                                    .parameters(
                                            {
                                                    SynthParameter("Aftertouch")
                                                            .number(180),
                                                    SynthParameter("Wheel")
                                                            .number(181),
                                                    SynthParameter("Breath")
                                                            .number(182),
                                                    SynthParameter("Foot")
                                                            .number(183)
                                            }
                                    ),
                            Section("Pulse Width LFO")
                                    .parameters(
                                            {
                                                    SynthParameter("Aftertouch")
                                                            .number(184),
                                                    SynthParameter("Wheel")
                                                            .number(185),
                                                    SynthParameter("Breath")
                                                            .number(186),
                                                    SynthParameter("Foot")
                                                            .number(187),
                                            }
                                    ),
//                            Section("Cutoff LFO")
//                                    .parameters(
//                                            {
//                                                    SynthParameter("Aftertouch")
//                                                            .number(188),
//                                                    SynthParameter("Wheel")
//                                                            .number(189),
//                                                    SynthParameter("Breath")
//                                                            .number(190),
//                                                    SynthParameter("Foot")
//                                                            .number(191),
//                                            }
//                                    ),
//                            Section("Amplitude LFO")
//                                    .parameters(
//                                            {
//                                                    SynthParameter("Aftertouch")
//                                                            .number(192),
//                                                    SynthParameter("Wheel")
//                                                            .number(193),
//                                                    SynthParameter("Breath")
//                                                            .number(194),
//                                                    SynthParameter("Foot")
//                                                            .number(195),
//                                            }
//                                    )
                    }
            );
}

Section SectionFactory::createPerformanceControlsSection() {
    return Section("Performance Ctrls")
            .parameters(
                    {
                            SynthParameter("Midi CC 70")
                                    .performanceControlType(400, 401),
                            SynthParameter("Midi CC 74")
                                    .performanceControlType(408, 409),
                            SynthParameter("Midi CC 71")
                                    .performanceControlType(402, 403),
                            SynthParameter("Midi CC 75")
                                    .performanceControlType(410, 411),
                            SynthParameter("Midi CC 72")
                                    .performanceControlType(404, 405),
                            SynthParameter("Midi CC 76")
                                    .performanceControlType(412, 413),
                            SynthParameter("Midi CC 73")
                                    .performanceControlType(406, 407),
                            SynthParameter("Midi CC 77")
                                    .performanceControlType(414, 415)
                    }

            );
}

Section SectionFactory::createSequencerSection() {
    return Section("Sequencer")
            .subSections(
                    {
                            Section("Main")
                                    .parameters(
                                            {
                                                    SynthParameter("On or Off")
                                                            .number(428)
                                                            .max(1)
                                                            .descriptions({"OFF", "ON"}),
                                                    SynthParameter("Steps")
                                                            .number(430)
                                                            .max(16),
                                                    SynthParameter("Tempo")
                                                            .number(431),
                                                    SynthParameter("Multiplier")
                                                            .number(432)
                                                            .min(1),
                                                    SynthParameter("Velocity")
                                                            .number(429),
                                                    SynthParameter("Transpose")
                                                            .number(433)
                                            }
                                    ),
                            Section("Steps")
                                    .parameters(
                                            {
                                                    SynthParameter("Step 1")
                                                            .number(434)
                                                            .type(MIDI_NOTE),
                                                    SynthParameter("Step 5")
                                                            .number(438)
                                                            .type(MIDI_NOTE),
                                                    SynthParameter("Step 2")
                                                            .number(435)
                                                            .type(MIDI_NOTE),
                                                    SynthParameter("Step 6")
                                                            .number(439)
                                                            .type(MIDI_NOTE),
                                                    SynthParameter("Step 3")
                                                            .number(436)
                                                            .type(MIDI_NOTE),
                                                    SynthParameter("Step 7")
                                                            .number(440)
                                                            .type(MIDI_NOTE),
                                                    SynthParameter("Step 4")
                                                            .number(437)
                                                            .type(MIDI_NOTE),
                                                    SynthParameter("Step 8")
                                                            .number(441)
                                                            .type(MIDI_NOTE),

                                                    SynthParameter("Step 9")
                                                            .number(442)
                                                            .type(MIDI_NOTE),
                                                    SynthParameter("Step 13")
                                                            .number(446)
                                                            .type(MIDI_NOTE),
                                                    SynthParameter("Step 10")
                                                            .number(443)
                                                            .type(MIDI_NOTE),
                                                    SynthParameter("Step 14")
                                                            .number(447)
                                                            .type(MIDI_NOTE),
                                                    SynthParameter("Step 11")
                                                            .number(444)
                                                            .type(MIDI_NOTE),
                                                    SynthParameter("Step 15")
                                                            .number(448)
                                                            .type(MIDI_NOTE),
                                                    SynthParameter("Step 12")
                                                            .number(445)
                                                            .type(MIDI_NOTE),
                                                    SynthParameter("Step 16")
                                                            .number(449)
                                                            .type(MIDI_NOTE)
                                            }
                                    )
                    }
            );
}
