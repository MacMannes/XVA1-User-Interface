//
// Created by André Mathlener on 16/04/2021.
//

#include "SectionFactory.h"
#include "SynthParameterBuilder.h"

Section *SectionFactory::createDefaultSection() {
    return new Section(
            "Default",
            {
                    SynthParameterBuilder("Cutoff")
                            .number(72)
                            .build(),

                    SynthParameterBuilder("Resonance")
                            .number(77)
                            .build(),

                    SynthParameterBuilder("Sequencer")
                            .number(428)
                            .max(1)
                            .descriptions({"OFF", "ON"})
                            .build()
            }
    );
}

Section *SectionFactory::createVoiceSection() {
    return new Section(
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
}

Section *SectionFactory::createMixerSection() {
    return new Section(
            "Mixer",
            {
                    Section(
                            "Output",
                            {
                                    SynthParameterBuilder("Volume")
                                            .number(509)
                                            .build(),
                                    SynthParameterBuilder("")
                                            .build(),
                                    SynthParameterBuilder("Gain Pre-FX")
                                            .number(510)
                                            .max(4)
                                            .descriptions({"0 dB", "+6 dB", "+12 dB", "+18 dB"})
                                            .build(),
                                    SynthParameterBuilder("")
                                            .build(),
                                    SynthParameterBuilder("Gain Post-FX")
                                            .number(511)
                                            .max(4)
                                            .descriptions({"0 dB", "+6 dB", "+12 dB", "+18 dB"})
                                            .build(),
                            }
                    ),
                    Section(
                            "Oscillator levels",
                            {
                                    SynthParameterBuilder("OSC 1")
                                            .number(27)
                                            .build(),
                                    SynthParameterBuilder("")
                                            .build(),
                                    SynthParameterBuilder("OSC 2")
                                            .number(28)
                                            .build(),
                                    SynthParameterBuilder("")
                                            .build(),
                                    SynthParameterBuilder("OSC 3")
                                            .number(29)
                                            .build(),
                                    SynthParameterBuilder("")
                                            .build(),
                                    SynthParameterBuilder("OSC 4")
                                            .number(30)
                                            .build(),
                            }
                    ),
                    Section(
                            "Oscillator Panning",
                            {
                                    SynthParameterBuilder("OSC 1 Level L")
                                            .number(31)
                                            .build(),
                                    SynthParameterBuilder("OSC 1 Level R")
                                            .number(32)
                                            .build(),
                                    SynthParameterBuilder("OSC 2 Level L")
                                            .number(33)
                                            .build(),
                                    SynthParameterBuilder("OSC 2 Level R")
                                            .number(34)
                                            .build(),
                                    SynthParameterBuilder("OSC 3 Level L")
                                            .number(35)
                                            .build(),
                                    SynthParameterBuilder("OSC 3 Level R")
                                            .number(36)
                                            .build(),
                                    SynthParameterBuilder("OSC 4 Level L")
                                            .number(37)
                                            .build(),
                                    SynthParameterBuilder("OSC 4 Level R")
                                            .number(38)
                                            .build(),
                            }
                    )
            }
    );
}

Section *SectionFactory::createEffectsSection() {
    return new Section(
            "Effects",
            {
                    Section(
                            "Bandwidth limit",
                            {
                                    SynthParameterBuilder("Bandwidth")
                                            .number(340)
                                            .max(7)
                                            .descriptions({
                                                                  "No filter", "20 kHz", "18 kHz", "16 kHz", "14 kHz",
                                                                  "12 kHz", "10 kHz", "8 kHz"
                                                          })
                                            .build(),
                            }
                    ),
                    Section(
                            "Distortion",
                            {
                                    SynthParameterBuilder("On or Off")
                                            .number(340)
                                            .max(1)
                                            .descriptions({"OFF", "ON"})
                                            .build(),
                                    SynthParameterBuilder("Type")
                                            .number(354)
                                            .max(3)
                                            .descriptions({"Hard clipping", "Soft clipping", "Tube 12AX", "Tube DSL"})
                                            .build(),
                                    SynthParameterBuilder("Gain PRE")
                                            .number(354)
                                            .build(),
                                    SynthParameterBuilder("Gain POST")
                                            .number(354)
                                            .build(),
                                    SynthParameterBuilder("Filter POST")
                                            .number(340)
                                            .max(7)
                                            .descriptions({
                                                                  "No filter", "20 kHz", "18 kHz", "16 kHz", "14 kHz",
                                                                  "12 kHz", "10 kHz", "8 kHz"
                                                          })
                                            .build(),
                            }

                    ),
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
}

Section *SectionFactory::createArpSection() {
    return new Section(
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
}

Section *SectionFactory::createOscillatorSection() {
    return new Section(
            "Oscillators",
            {"Oscillator 1", "Oscillator 2", "Oscillator 3", "Oscillator 4"},
            {
                    SynthParameterBuilder("On or Off")
                            .numbers({1, 2, 3, 4})
                            .max(1)
                            .descriptions({"OFF", "ON"})
                            .build(),

                    SynthParameterBuilder("Mode")
                            .type(BITWISE)
                            .number(6)
                            .bitNumbers({0, 1, 2, 3})
                            .descriptions({"KeyTrack", "FixedPitch"})
                            .build(),


                    SynthParameterBuilder("Sync")
                            .type(BITWISE)
                            .number(5)
                            .bitNumbers({0, 1, 2, 3})
                            .descriptions({"Free running", "Restart on Key-ON"})
                            .build(),

                    SynthParameterBuilder("Waveform")
                            .numbers({11, 12, 13, 14})
                            .max(8)
                            .descriptions(
                                    {"Saw up", "Saw down", "Square", "Triangle", "Sine",
                                     "Noise", "Sawstack x3 (stereo)",
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
}

Section *SectionFactory::createEnvelopeSection() {
    return new Section(
            "Envelopes",
            {"PITCH", "CUTOFF", "AMP"},
            {
                    SynthParameterBuilder("L0 - Start")
                            .numbers({80, 81, 82})
                            .build(),
                    SynthParameterBuilder("L4 - Release 1")
                            .numbers({100, 101, 102})
                            .build(),
                    SynthParameterBuilder("L1 - Attack")
                            .numbers({85, 86, 88})
                            .build(),
                    SynthParameterBuilder("L5 - Release 2")
                            .numbers({105, 106, 107})
                            .build(),
                    SynthParameterBuilder("L2 - Decay")
                            .numbers({90, 91, 92})
                            .build(),
                    SynthParameterBuilder("")
                            .build(),
                    SynthParameterBuilder("L3 - Sustain")
                            .numbers({95, 96, 97})
                            .build(),
                    SynthParameterBuilder("Delay")
                            .numbers({110, 111, 112})
                            .build(),
                    SynthParameterBuilder("R1 - Attack")
                            .numbers({115, 116, 117})
                            .build(),
                    SynthParameterBuilder("R5 - Release 2")
                            .numbers({135, 136, 137})
                            .build(),
                    SynthParameterBuilder("R2 - Decay")
                            .numbers({120, 121, 122})
                            .build(),
                    SynthParameterBuilder("")
                            .build(),
                    SynthParameterBuilder("R3 - Sustain")
                            .numbers({125, 126, 127})
                            .build(),
                    SynthParameterBuilder("")
                            .build(),
                    SynthParameterBuilder("R4 - Release 1")
                            .numbers({130, 131, 132})
                            .build(),
                    SynthParameterBuilder("")
                            .build(),

                    SynthParameterBuilder("EG Loop")
                            .type(BITWISE)
                            .number(145)
                            .bitNumbers({0, 1, 6})
                            .descriptions({"Normal", "Loop"})
                            .build(),
                    SynthParameterBuilder("")
                            .build(),
                    SynthParameterBuilder("EG Loop Segment")
                            .type(BITWISE)
                            .number(146)
                            .bitNumbers({0, 1, 6})
                            .descriptions({"L0 - Attack", "L5 - Decay"})
                            .build(),
                    SynthParameterBuilder("")
                            .build(),
                    SynthParameterBuilder("EG Restart from")
                            .type(BITWISE)
                            .number(147)
                            .bitNumbers({0, 1, 6})
                            .descriptions({"L5 - Decay", "L0 - Start"})
                            .build(),
                    SynthParameterBuilder("")
                            .build(),
                    SynthParameterBuilder("Range")
                            .numbers({148, -1, -1})
                            .max(10)
                            .build(),
                    SynthParameterBuilder("Velocity")
                            .numbers({149, -1, -1})
                            .max(10)
                            .build(),

            }
    );
}

Section *SectionFactory::createLFOSection() {
    return new Section(
            "LFO",
            {"LFO1", "LFO2"},
            {
                    SynthParameterBuilder("Wave")
                            .numbers({160, 170})
                            .max(9)
                            .build()
            }
    );
}

Section *SectionFactory::createFilterSection() {
    return new Section(
            "Filters",
            {
                    Section("Filter 1",
                            {

                                    SynthParameterBuilder("Cutoff")
                                            .number(72)
                                            .build(),

                                    SynthParameterBuilder("Resonance")
                                            .number(77)
                                            .build()
                            }
                    ),
                    Section("Filter 2",
                            {
                                    SynthParameterBuilder("Cutoff")
                                            .number(78)
                                            .build(),

                                    SynthParameterBuilder("Resonance")
                                            .number(79)
                                            .build()
                            }
                    ),
                    Section("Settings",
                            {

                                    SynthParameterBuilder("Type")
                                            .number(71)
                                            .max(21)
                                            .descriptions({
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
                                                          })
                                            .build(),
                                    SynthParameterBuilder("Velocity")
                                            .type(CENTER_128)
                                            .number(73)
                                            .build(),
                                    SynthParameterBuilder("KBD Track")
                                            .type(CENTER_128)
                                            .number(74)
                                            .build(),
                                    SynthParameterBuilder("EG depth")
                                            .type(CENTER_128)
                                            .number(75)
                                            .build(),
                                    SynthParameterBuilder("EG Velocity")
                                            .type(CENTER_128)
                                            .number(76)
                                            .build(),
                                    SynthParameterBuilder("Velocity RESO")
                                            .type(CENTER_128)
                                            .number(276)
                                            .build(),
                                    SynthParameterBuilder("KBD Track RESO")
                                            .type(CENTER_128)
                                            .number(277)
                                            .build(),
                                    SynthParameterBuilder("Drive")
                                            .number(275)
                                            .max(7)
                                            .build(),
                                    SynthParameterBuilder("Routing")
                                            .number(278)
                                            .max(1)
                                            .descriptions({"Standard", "LR Mode"})
                                            .build(),
                            }
                    )
            }

    );
}

Section *SectionFactory::createPatchSection() {
    return new Section(
            "Patch",
            {
                    SynthParameterBuilder("")
                            .build(),
            }
    );
}

Section *SectionFactory::createExternalControlsSection() {
    return new Section(
            "External Ctrls",
            {
                    SynthParameterBuilder("")
                            .build(),
            }
    );
}

Section *SectionFactory::createPerformanceControlsSection() {
    return new Section(
            "Performance Ctrls",
            {
                    SynthParameterBuilder("Midi CC 70")
                            .performanceControlType(400, 401)
                            .build(),
                    SynthParameterBuilder("Midi CC 74")
                            .performanceControlType(408, 409)
                            .build(),
                    SynthParameterBuilder("Midi CC 71")
                            .performanceControlType(402, 403)
                            .build(),
                    SynthParameterBuilder("Midi CC 75")
                            .performanceControlType(410, 411)
                            .build(),
                    SynthParameterBuilder("Midi CC 72")
                            .performanceControlType(404, 405)
                            .build(),
                    SynthParameterBuilder("Midi CC 76")
                            .performanceControlType(412, 413)
                            .build(),
                    SynthParameterBuilder("Midi CC 73")
                            .performanceControlType(406, 407)
                            .build(),
                    SynthParameterBuilder("Midi CC 77")
                            .performanceControlType(414, 415)
                            .build()
            }

    );
}

Section *SectionFactory::createSequencerSection() {
    return new Section(
            "Sequencer",
        {
                Section(
                        "Main",
                        {
                                SynthParameterBuilder("On or Off")
                                        .number(428)
                                        .max(1)
                                        .descriptions({"OFF", "ON"})
                                        .build(),
                                SynthParameterBuilder("Steps")
                                        .number(430)
                                        .max(16)
                                        .build(),
                                SynthParameterBuilder("Tempo")
                                        .number(431)
                                        .build(),
                                SynthParameterBuilder("Multiplier")
                                        .number(432)
                                        .min(1)
                                        .build(),
                                SynthParameterBuilder("Velocity")
                                        .number(429)
                                        .build(),
                                SynthParameterBuilder("Transpose")
                                        .number(433)
                                        .build(),
                        }
                ),
                Section(
                        "Steps",
            {
                    SynthParameterBuilder("Step 1")
                            .number(434)
                            .type(MIDI_NOTE)
                            .build(),
                    SynthParameterBuilder("Step 5")
                            .number(438)
                            .type(MIDI_NOTE)
                            .build(),
                    SynthParameterBuilder("Step 2")
                            .number(435)
                            .type(MIDI_NOTE)
                            .build(),
                    SynthParameterBuilder("Step 6")
                            .number(439)
                            .type(MIDI_NOTE)
                            .build(),
                    SynthParameterBuilder("Step 3")
                            .number(436)
                            .type(MIDI_NOTE)
                            .build(),
                    SynthParameterBuilder("Step 7")
                            .number(440)
                            .type(MIDI_NOTE)
                            .build(),
                    SynthParameterBuilder("Step 4")
                            .number(437)
                            .type(MIDI_NOTE)
                            .build(),
                    SynthParameterBuilder("Step 8")
                            .number(441)
                            .type(MIDI_NOTE)
                            .build(),

                    SynthParameterBuilder("Step 9")
                            .number(442)
                            .type(MIDI_NOTE)
                            .build(),
                    SynthParameterBuilder("Step 13")
                            .number(446)
                            .type(MIDI_NOTE)
                            .build(),
                    SynthParameterBuilder("Step 10")
                            .number(443)
                            .type(MIDI_NOTE)
                            .build(),
                    SynthParameterBuilder("Step 14")
                            .number(447)
                            .type(MIDI_NOTE)
                            .build(),
                    SynthParameterBuilder("Step 11")
                            .number(444)
                            .type(MIDI_NOTE)
                            .build(),
                    SynthParameterBuilder("Step 15")
                            .number(448)
                            .type(MIDI_NOTE)
                            .build(),
                    SynthParameterBuilder("Step 12")
                            .number(445)
                            .type(MIDI_NOTE)
                            .build(),
                    SynthParameterBuilder("Step 16")
                            .number(449)
                            .type(MIDI_NOTE)
                            .build()
                        }
                )
            }
    );
}
