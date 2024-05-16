//
// Created by Saqib Bhatti on 16/5/24.
//

#ifndef PONG_BAT_H
#define PONG_BAT_H

#include <SFML/Graphics.hpp>


using namespace sf;


class Bat {
private:
    Vector2f m_Position{};  // will hold the horizontal and vertical position of the player's bat.

    // A RectangleShape object
    RectangleShape m_Shape{};

    float m_Speed = 1000.0f;  // tells us the number of pixels per second that the bat can move at when the player
    // decides to move it left or right.
    bool m_MovingRight = false;
    bool m_MovingLeft = false;

public:
    Bat(float startX, float startY);  // initializing the position on the screen when we first create a Bat object.
    FloatRect getPosition();  // returns a FloatRect, the four points that define a rectangle.
    RectangleShape getShape();
    void moveLeft();
    void moveRight();
    void stopLeft();
    void stopRight();
    void update(Time dt);  // This function will be used to calculate how to move the bat each frame.

};

#endif //PONG_BAT_H
