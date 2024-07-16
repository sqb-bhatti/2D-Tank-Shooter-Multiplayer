//
// Created by Saqib Bhatti on 16/7/24.
//

#ifndef TWL_THOMAS_H
#define TWL_THOMAS_H

#include "PlayableCharacter.h"


class Thomas: public PlayableCharacter {
public:
    // A constructor specific to Thomas
    Thomas();

    // The overridden input handler for Thomas
    bool virtual handleInput();
};


#endif //TWL_THOMAS_H
