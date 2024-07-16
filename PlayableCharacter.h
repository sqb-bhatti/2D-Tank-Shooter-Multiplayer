
//
// Created by Saqib Bhatti on 16/7/24.
//

#ifndef TWL_PLAYABLECHARACTER_H
#define TWL_PLAYABLECHARACTER_H

#include <SFML/Graphics.hpp>


using namespace sf;


class PlayableCharacter {
protected:
    Sprite m_Sprite;

    // hold a value representing the time that the character is able to jump for.
    // The greater the value, the further/higher the character will be able to jump.
    float m_JumpDuration;

    // Is character currently jumping or falling
    bool m_IsJumping;
    bool m_IsFalling;

    // Which directions is the character currently moving in
    bool m_LeftPressed;
    bool m_RightPressed;

    // How long has this jump lasted so far
    float m_TimeThisJump;

    // Has the player just initiated a jump
    bool m_JustJumped = false;

private:
    // number of pixels per second that the character will fall.
    float m_Gravity;

    // How fast is the character
    float m_Speed = 400;

    Vector2f m_Position;

    // Where are the characters various body parts? will hold the coordinates of the different parts of a
    //character's body. These coordinates will be updated each frame.
    FloatRect m_Feet;
    FloatRect m_Head;
    FloatRect m_Right;
    FloatRect m_Left;

    Texture m_Texture;

public:
    void spawn(Vector2f startPosition, float gravity);
    bool virtual handleInput() = 0;  // Pure Virtual function

    // Where is the player. represents the position of the whole character.
    FloatRect getPosition();

    // These 4 methods represents the location of a specific
    // part of the character's body. This is just what we need for detailed collision detection.
    FloatRect getFeet();
    FloatRect getHead();
    FloatRect getRight();
    FloatRect getLeft();

    // Send a copy of the sprite to main
    Sprite getSprite();

    void stopFalling(float position);
    void stopRight(float position);
    void stopLeft(float position);
    void stopJump();

    // Where is the center of the character
    Vector2f getCenter();

    void update(float elapsedTime);
};


#endif //TWL_PLAYABLECHARACTER_H
