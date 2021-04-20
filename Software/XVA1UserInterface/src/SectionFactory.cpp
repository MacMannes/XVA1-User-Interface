//
// Created by André Mathlener on 16/04/2021.
//

#include "SectionFactory.h"
#include "SynthParameter.h"

Section SectionFactory::createDefaultSection() {
    return Section("Default")
            .addParameter(SynthParameter("Cutoff").number(72))
            .addParameter(SynthParameter("Resonance").number(77))
            .addParameter(
                    SynthParameter("Sequencer")
                            .number(428)
                            .max(1)
                            .descriptions({"OFF", "ON"})
            );
}

Section SectionFactory::createVoiceSection() {
    return Section("Voice")
            .addParameter(
                    SynthParameter("Transpose")
                            .type(CENTER_128)
                            .number(241)
            )
            .addParameter(SynthParameter("Bend Up").number(242))
            .addParameter(SynthParameter("Bend Down").number(243));
}

Section SectionFactory::createMixerSection() {
    return Section("Mixer")
            .addSubSection(
                    Section("Output")
                            .addParameter(SynthParameter("Volume").number(509))
                            .addParameter(SynthParameter(""))
                            .addParameter(
                                    SynthParameter("Gain Pre-FX")
                                            .number(510)
                                            .max(4)
                                            .descriptions({"0 dB", "+6 dB", "+12 dB", "+18 dB"})
                            )
                            .addParameter(SynthParameter(""))
                            .addParameter(
                                    SynthParameter("Gain Post-FX")
                                            .number(511)
                                            .max(4)
                                            .descriptions({"0 dB", "+6 dB", "+12 dB", "+18 dB"})
                            )

            )
            .addSubSection(
                    Section("Oscillator levels")
                            .addParameter(SynthParameter("OSC 1").number(27))
                            .addParameter(SynthParameter(""))
                            .addParameter(SynthParameter("OSC 2").number(28))
                            .addParameter(SynthParameter(""))
                            .addParameter(SynthParameter("OSC 3").number(29))
                            .addParameter(SynthParameter(""))
                            .addParameter(SynthParameter("OSC 4").number(30))

            )
            .addSubSection(
                    Section("Oscillator Panning")
                            .addParameter(SynthParameter("OSC 1 Level L").number(31))
                            .addParameter(SynthParameter("OSC 1 Level R").number(32))
                            .addParameter(SynthParameter("OSC 2 Level L").number(33))
                            .addParameter(SynthParameter("OSC 2 Level R").number(34))
                            .addParameter(SynthParameter("OSC 3 Level L").number(35))
                            .addParameter(SynthParameter("OSC 3 Level R").number(36))
                            .addParameter(SynthParameter("OSC 4 Level L").number(37))
                            .addParameter(SynthParameter("OSC 4 Level R").number(38))
            );
}

Section SectionFactory::createEffectsSection() {
    return Section("Effects")
            .addSubSection(
                    Section("Bandwidth limit")
                            .addParameter(
                                    SynthParameter("Bandwidth")
                                            .number(340)
                                            .max(7)
                                            .descriptions({"No filter", "20 kHz", "18 kHz", "16 kHz",
                                                           "14 kHz", "12 kHz", "10 kHz", "8 kHz"})
                            )
            )
            .addSubSection(
                    Section("Distortion")
                            .addParameter(
                                    SynthParameter("On or Off")
                                            .number(340)
                                            .max(1)
                                            .descriptions({"OFF", "ON"})
                            )
                            .addParameter(
                                    SynthParameter("Type")
                                            .number(354)
                                            .max(3)
                                            .descriptions(
                                                    {"Hard clipping", "Soft clipping", "Tube 12AX",
                                                     "Tube DSL"})
                            )
                            .addParameter(SynthParameter("Gain PRE").number(354))
                            .addParameter(SynthParameter("Gain POST").number(354))
                            .addParameter(
                                    SynthParameter("Filter POST")
                                            .number(340)
                                            .max(7)
                                            .descriptions({"No filter", "20 kHz", "18 kHz", "16 kHz",
                                                           "14 kHz", "12 kHz", "10 kHz", "8 kHz"})
                            )
            )
            .addSubSection(
                    Section("Chorus/Flanger")
                            .addParameter(SynthParameter("DRY").number(360))
                            .addParameter(SynthParameter("WET").number(351))
            )
            .addSubSection(
                    Section("Phaser")
                            .addParameter(SynthParameter("DRY").number(310))
                            .addParameter(SynthParameter("WET").number(311))
            )
            .addSubSection(
                    Section("Delay")
                            .addParameter(SynthParameter("DRY").number(300))
                            .addParameter(SynthParameter("WET").number(301))
            );
}

Section SectionFactory::createArpSection() {
    return Section("ARP")
            .addParameter(SynthParameter("MODE").number(450))
            .addParameter(
                    SynthParameter("Temp")
                            .number(451)
                            .min(44)
            );
}

Section SectionFactory::createOscillatorSection() {
    return Section("Oscillators")
            .virtualSubSectionTitles({"Oscillator 1", "Oscillator 2", "Oscillator 3", "Oscillator 4"})
            .addParameter(
                    SynthParameter("On or Off")
                            .numbers({1, 2, 3, 4})
                            .max(1)
                            .descriptions({"OFF", "ON"})
            )
            .addParameter(
                    SynthParameter("Mode")
                            .type(BITWISE)
                            .number(6)
                            .bitNumbers({0, 1, 2, 3})
                            .descriptions({"KeyTrack", "FixedPitch"})
            )
            .addParameter(
                    SynthParameter("Sync")
                            .type(BITWISE)
                            .number(5)
                            .bitNumbers({0, 1, 2, 3})
                            .descriptions({"Free running", "Restart on Key-ON"})
            )
            .addParameter(
                    SynthParameter("Waveform")
                            .numbers({11, 12, 13, 14})
                            .max(8)
                            .descriptions({"Saw up", "Saw down", "Square", "Triangle", "Sine",
                                           "Noise", "Sawstack x3 (stereo)",
                                           "Sawstack x7 (mono)", "Sawstack x7 (stereo)"})
            )
            .addParameter(
                    SynthParameter("Phase")
                            .numbers({7, 8, 9, 10})
                            .max(3)
                            .descriptions({"0 deg", "90 deg", "180 deg", "270 deg"})
            )
            .addParameter(
                    SynthParameter("Pulse Width")
                            .type(CENTER_128)
                            .numbers({15, 16, 17, 18})
            )
            .addParameter(
                    SynthParameter("Transpose")
                            .type(CENTER_128)
                            .numbers({19, 20, 21, 22})
            )
            .addParameter(
                    SynthParameter("Detune")
                            .type(CENTER_128)
                            .numbers({23, 24, 25, 26})
            )
            .addParameter(SynthParameter("Sawstack Detune").numbers({285, 286, 287, 288}))
            .addParameter(SynthParameter("Drift").numbers({260, 261, 262, 263}))
            .addParameter(SynthParameter("Key breakpoint").numbers({43, 44, 45, 46}))
            .addParameter(SynthParameter("Key L depth").numbers({47, 48, 49, 50}))
            .addParameter(SynthParameter("Key R depth").numbers({51, 52, 53, 54}))
            .addParameter(SynthParameter("Key L curve").numbers({55, 56, 57, 58}))
            .addParameter(SynthParameter("Key R curve").numbers({59, 60, 61, 62}))
            .addParameter(SynthParameter("PMS").numbers({63, 64, 65, 66}))
            .addParameter(SynthParameter("AMS").numbers({67, 66, 67, 68}));
}

Section SectionFactory::createEnvelopeSection() {
    return Section("Envelopes")
            .virtualSubSectionTitles({"PITCH", "CUTOFF", "AMP"})
            .addParameter(SynthParameter("L0 - Start").numbers({80, 81, 82}))
            .addParameter(SynthParameter("L4 - Release 1").numbers({100, 101, 102}))
            .addParameter(SynthParameter("L1 - Attack").numbers({85, 86, 88}))
            .addParameter(SynthParameter("L5 - Release 2").numbers({105, 106, 107}))
            .addParameter(SynthParameter("L2 - Decay").numbers({90, 91, 92}))
            .addParameter(SynthParameter(""))
            .addParameter(SynthParameter("L3 - Sustain").numbers({95, 96, 97}))
            .addParameter(SynthParameter("Delay").numbers({110, 111, 112}))
            .addParameter(SynthParameter("R1 - Attack").numbers({115, 116, 117}))
            .addParameter(SynthParameter("R5 - Release 2").numbers({135, 136, 137}))
            .addParameter(SynthParameter("R2 - Decay").numbers({120, 121, 122}))
            .addParameter(SynthParameter(""))
            .addParameter(SynthParameter("R3 - Sustain").numbers({125, 126, 127}))
            .addParameter(SynthParameter(""))
            .addParameter(SynthParameter("R4 - Release 1").numbers({130, 131, 132}))
            .addParameter(SynthParameter(""))
            .addParameter(
                    SynthParameter("EG Loop")
                            .type(BITWISE)
                            .number(145)
                            .bitNumbers({0, 1, 6})
                            .descriptions({"Normal", "Loop"})
            )
            .addParameter(SynthParameter(""))
            .addParameter(
                    SynthParameter("EG Loop Segment")
                            .type(BITWISE)
                            .number(146)
                            .bitNumbers({0, 1, 6})
                            .descriptions({"L0 - Attack", "L5 - Decay"})
            )
            .addParameter(SynthParameter(""))
            .addParameter(
                    SynthParameter("EG Restart from")
                            .type(BITWISE)
                            .number(147)
                            .bitNumbers({0, 1, 6})
                            .descriptions({"L5 - Decay", "L0 - Start"})
            )
            .addParameter(SynthParameter(""))
            .addParameter(
                    SynthParameter("Range")
                            .numbers({148, -1, -1})
                            .max(10)
            )
            .addParameter(
                    SynthParameter("Velocity")
                            .numbers({149, -1, -1})
                            .max(10)
            );
}

Section SectionFactory::createLFOSection() {
    return Section("LFO")
            .addSubSection(
                    Section("LFO1")
                            .addParameter(
                                    SynthParameter("Wave")
                                            .number(160)
                                            .max(9)
                                            .descriptions({"Triangle", "Square", "Saw Up", "Saw Down", "Sine",
                                                           "Sin( x ) + Sin( 2x )", "Sin( x ) + Sin( 3x )",
                                                           "Sin( x ) ^ 3", "Guitar", "S & H"})
                            )
                            .addParameter(SynthParameter("Range").number(166))
                            .addParameter(SynthParameter("Speed").number(161))
                            .addParameter(
                                    SynthParameter("Sync")
                                            .number(162)
                                            .descriptions({"Single, Free running", "Single, Key sync",
                                                           "Multi, Free running", "Multi, Key sync"})
                            )
                            .addParameter(SynthParameter("Fade").number(163))
                            .addParameter(SynthParameter("Depth Pitch").number(164))
                            .addParameter(SynthParameter("AMP Pitch").number(165))
            )
            .addSubSection(
                    Section("LFO2")
                            .addParameter(
                                    SynthParameter("Wave")
                                            .number(170)
                                            .max(9)
                                            .descriptions({"Triangle", "Square", "Saw Up", "Saw Down", "Sine",
                                                           "Sin( x ) + Sin( 2x )", "Sin( x ) + Sin( 3x )",
                                                           "Sin( x ) ^ 3", "Guitar", "S & H"})
                            )
                            .addParameter(SynthParameter("Range").number(176))
                            .addParameter(SynthParameter("Speed").number(171))
                            .addParameter(
                                    SynthParameter("Sync")
                                            .number(172)
                                            .descriptions({"Single, Free running", "Single, Key sync",
                                                           "Multi, Free running", "Multi, Key sync"})
                            )
                            .addParameter(SynthParameter("Fade").number(173))
                            .addParameter(SynthParameter("Depth Pitch").number(174))
                            .addParameter(SynthParameter("AMP Pitch").number(175))
            );
}

Section SectionFactory::createFilterSection() {
    return Section("Filters")
            .addSubSection(
                    Section("Filter 1")
                            .addParameter(SynthParameter("Cutoff").number(72))
                            .addParameter(SynthParameter("Resonance").number(77))
            )
            .addSubSection(
                    Section("Filter 2")
                            .addParameter(SynthParameter("Cutoff").number(78))
                            .addParameter(SynthParameter("Resonance").number(79))
            )
            .addSubSection(
                    Section("Settings")
                            .addParameter(
                                    SynthParameter("Type")
                                            .number(71)
                                            .max(21)
                                            .descriptions({"Bypass", "LPF 1P", "LPF 2P", "LPF 3P", "LPF 4P", "HPF 1P",
                                                           "HPF 2P", "HPF 3P", "HPF 4P", "BPF 2P", "BPF 4P", "BRF 2P",
                                                           "BRF 4P", "LP -> LP", "LP -> BP", "LP -> HP", "LP // LP",
                                                           "LP // BP", "LP // HP", "BP // BP", "BP // HP", "HP // HP"})
                            )
                            .addParameter(
                                    SynthParameter("Velocity")
                                            .type(CENTER_128)
                                            .number(73)
                            )
                            .addParameter(
                                    SynthParameter("KBD Track")
                                            .type(CENTER_128)
                                            .number(74)
                            )
                            .addParameter(
                                    SynthParameter("EG depth")
                                            .type(CENTER_128)
                                            .number(75)
                            )
                            .addParameter(
                                    SynthParameter("EG Velocity")
                                            .type(CENTER_128)
                                            .number(76)
                            )
                            .addParameter(
                                    SynthParameter("Velocity RESO")
                                            .type(CENTER_128)
                                            .number(276)
                            )
                            .addParameter(
                                    SynthParameter("KBD Track RESO")
                                            .type(CENTER_128)
                                            .number(277)
                            )
                            .addParameter(
                                    SynthParameter("Drive")
                                            .number(275)
                                            .max(7)
                            )
                            .addParameter(
                                    SynthParameter("Routing")
                                            .number(278)
                                            .max(1)
                                            .descriptions({"Standard", "LR Mode"})
                            )
            );
}

Section SectionFactory::createPatchSection() {
    return Section("Patch")
            .addParameter(SynthParameter(""));
}

Section SectionFactory::createExternalControlsSection() {
    return Section("External Ctrls")
            .addSubSection(
                    Section("Pitch")
                            .addParameter(
                                    SynthParameter("Aftertouch")
                                            .number(200)
                                            .type(CENTER_128)
                            )
                            .addParameter(
                                    SynthParameter("Breath")
                                            .number(201)
                                            .type(CENTER_128)
                            )
                            .addParameter(
                                    SynthParameter("Foot")
                                            .number(202)
                                            .type(CENTER_128)
                            )
                            .addParameter(
                                    SynthParameter("Temperature")
                                            .number(220)
                                            .type(CENTER_128)
                            )
                            .addParameter(
                                    SynthParameter("CV-1")
                                            .number(221)
                                            .type(CENTER_128)

                            )
                            .addParameter(
                                    SynthParameter("CV-2")
                                            .number(222)
                                            .type(CENTER_128)

                            )
                            .addParameter(SynthParameter("Random").number(203))
            )
            .addSubSection(
                    Section("Pulse Width")
                            .addParameter(
                                    SynthParameter("Aftertouch")
                                            .number(204)
                                            .type(CENTER_128)
                            )
                            .addParameter(
                                    SynthParameter("Wheel")
                                            .number(205)
                                            .type(CENTER_128)
                            )
                            .addParameter(
                                    SynthParameter("Breath")
                                            .number(206)
                                            .type(CENTER_128)
                            )
                            .addParameter(
                                    SynthParameter("Foot")
                                            .number(207)
                                            .type(CENTER_128)
                            )
                            .addParameter(
                                    SynthParameter("Temperature")
                                            .number(223)
                                            .type(CENTER_128)
                            )
                            .addParameter(
                                    SynthParameter("CV-1")
                                            .number(224)
                                            .type(CENTER_128)
                            )
                            .addParameter(
                                    SynthParameter("CV-2")
                                            .number(225)
                                            .type(CENTER_128)
                            )
            )
            .addSubSection(
                    Section("Cutoff")
                            .addParameter(
                                    SynthParameter("Aftertouch")
                                            .number(208)
                                            .type(CENTER_128)
                            )
                            .addParameter(
                                    SynthParameter("Wheel")
                                            .number(209)
                                            .type(CENTER_128)
                            )
                            .addParameter(
                                    SynthParameter("Breath")
                                            .number(210)
                                            .type(CENTER_128)
                            )
                            .addParameter(
                                    SynthParameter("Foot")
                                            .number(211)
                                            .type(CENTER_128)
                            )
                            .addParameter(
                                    SynthParameter("Temperature")
                                            .number(226)
                                            .type(CENTER_128)
                            )
                            .addParameter(
                                    SynthParameter("CV-1")
                                            .number(227)
                                            .type(CENTER_128)
                            )
                            .addParameter(
                                    SynthParameter("CV-2")
                                            .number(228)
                                            .type(CENTER_128)
                            )
            )
            .addSubSection(
                    Section("Volume")
                            .addParameter(
                                    SynthParameter("Aftertouch")
                                            .number(212)
                                            .type(CENTER_128)
                            )
                            .addParameter(
                                    SynthParameter("Wheel")
                                            .number(213)
                                            .type(CENTER_128)
                            )
                            .addParameter(
                                    SynthParameter("Breath")
                                            .number(214)
                                            .type(CENTER_128)
                            )
                            .addParameter(
                                    SynthParameter("Foot")
                                            .number(215)
                                            .type(CENTER_128)
                            )
                            .addParameter(
                                    SynthParameter("Temperature")
                                            .number(228)
                                            .type(CENTER_128)//
                            )
                            .addParameter(
                                    SynthParameter("CV-1")
                                            .number(230)
                                            .type(CENTER_128)
                            )
                            .addParameter(
                                    SynthParameter("CV-2")
                                            .number(231)
                                            .type(CENTER_128)
                            )
            )
            .addSubSection(
                    Section("Pitch LFO")
                            .addParameter(SynthParameter("Aftertouch").number(180))
                            .addParameter(SynthParameter("Wheel").number(181))
                            .addParameter(SynthParameter("Breath").number(182))
                            .addParameter(SynthParameter("Foot").number(183))
            )
            .addSubSection(
                    Section("Pulse Width LFO")
                            .addParameter(SynthParameter("Aftertouch").number(184))
                            .addParameter(SynthParameter("Wheel").number(185))
                            .addParameter(SynthParameter("Breath").number(186))
                            .addParameter(SynthParameter("Foot").number(187))
            )
            .addSubSection(
                    Section("Cutoff LFO")
                            .addParameter(SynthParameter("Aftertouch").number(188))
                            .addParameter(SynthParameter("Wheel").number(189))
                            .addParameter(SynthParameter("Breath").number(190))
                            .addParameter(SynthParameter("Foot").number(191))

            )
            .addSubSection(
                    Section("Amplitude LFO")
                            .addParameter(SynthParameter("Aftertouch").number(192))
                            .addParameter(SynthParameter("Wheel").number(193))
                            .addParameter(SynthParameter("Breath").number(194))
                            .addParameter(SynthParameter("Foot").number(195))
            );
}

Section SectionFactory::createPerformanceControlsSection() {
    return Section("Performance Ctrls")
            .addParameter(SynthParameter("Midi CC 70").performanceControlType(400, 401))
            .addParameter(SynthParameter("Midi CC 70").performanceControlType(400, 401))
            .addParameter(SynthParameter("Midi CC 74").performanceControlType(408, 409))
            .addParameter(SynthParameter("Midi CC 71").performanceControlType(402, 403))
            .addParameter(SynthParameter("Midi CC 75").performanceControlType(410, 411))
            .addParameter(SynthParameter("Midi CC 72").performanceControlType(404, 405))
            .addParameter(SynthParameter("Midi CC 76").performanceControlType(412, 413))
            .addParameter(SynthParameter("Midi CC 73").performanceControlType(406, 407))
            .addParameter(SynthParameter("Midi CC 77").performanceControlType(414, 415));
}

Section SectionFactory::createSequencerSection() {
    return Section("Sequencer")
            .addSubSection(
                    Section("Main")
                            .addParameter(
                                    SynthParameter("On or Off")
                                            .number(428)
                                            .max(1)
                                            .descriptions({"OFF", "ON"})
                            )
                            .addParameter(SynthParameter("Steps").number(430).max(16))
                            .addParameter(SynthParameter("Tempo").number(431))
                            .addParameter(SynthParameter("Multiplier").number(432).min(1))
                            .addParameter(SynthParameter("Velocity").number(429))
                            .addParameter(SynthParameter("Transpose").number(433))

            )
            .addSubSection(
                    Section("Steps")
                            .addParameter(SynthParameter("Step 1").number(434).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 5").number(438).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 2").number(435).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 6").number(439).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 3").number(436).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 7").number(440).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 4").number(437).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 8").number(441).type(MIDI_NOTE))

                            .addParameter(SynthParameter("Step 9").number(442).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 13").number(446).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 10").number(443).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 14").number(447).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 11").number(444).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 15").number(448).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 12").number(445).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 16").number(449).type(MIDI_NOTE))

            );
}
