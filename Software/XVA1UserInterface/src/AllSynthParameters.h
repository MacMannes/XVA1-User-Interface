//
// Created by André Mathlener on 30/04/2021.
//

#ifndef XVA1USERINTERFACE_ALLSYNTHPARAMETERS_H
#define XVA1USERINTERFACE_ALLSYNTHPARAMETERS_H

#include "SectionFactory.h"

Section sections[] = {
        SectionFactory().createDefaultSection(),
        SectionFactory().createVoiceSection(),
        SectionFactory().createMixerSection(),
        SectionFactory().createEffectsSection(),
        SectionFactory().createArpSection(),
        SectionFactory().createOscillatorSection(),
        SectionFactory().createEnvelopeSection(),
        SectionFactory().createLFOSection(),
        SectionFactory().createFilterSection(),
        SectionFactory().createPatchSection(),
        SectionFactory().createExternalControlsSection(),
        SectionFactory().createPerformanceControlsSection(),
        SectionFactory().createSequencerSection()
};

#endif //XVA1USERINTERFACE_ALLSYNTHPARAMETERS_H
