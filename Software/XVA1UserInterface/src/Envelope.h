//
// Created by André Mathlener on 30/04/2021.
//

#ifndef XVA1USERINTERFACE_ENVELOPE_H
#define XVA1USERINTERFACE_ENVELOPE_H

//Typedef for envelope
//l0 = level at start of the envelope
//l1 = level after the attack phase
//l2 = level after the decay-1 phase
//l3 = level after the decay-2 phase (= sustain level)
//l4 = level after the release-1 phase
//l5 = level after the release-2 phase (= end level)
//dly = time for the envelope to start
//r1 = rate of the attack phase (0 = slow, 255 = fast)
//r2 = rate of the decay-1 phase
//r3 = rate of the decay-2 phase
//r4 = rate of the release-1 phase
//r5 = rate of the release-2 phase
typedef struct {
    uint8_t level[6]; //l0, l1, l2, l3, l4, l5
    uint8_t rate[6];  //dly, r1, r2, r3, r4, r5
} Envelope;

#endif //XVA1USERINTERFACE_ENVELOPE_H
