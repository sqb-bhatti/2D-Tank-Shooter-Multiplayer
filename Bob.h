//
// Created by Saqib Bhatti on 16/7/24.
//

#ifndef TWL_BOB_H
#define TWL_BOB_H


#include "PlayableCharacter.h"


class Bob: public PlayableCharacter {
public:
    // A constructor specific to Bob
    Bob();

    // The overriden input handler for Bob
    bool virtual handleInput();
};


#endif //TWL_BOB_H
