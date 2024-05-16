//
// Created by Saqib Bhatti on 16/5/24.
//

#ifndef PONG_BALL_H
#define PONG_BALL_H

#include <SFML/Graphics.hpp>


using namespace sf;


class Ball {
private:
    Vector2f m_Position{};

    RectangleShape m_Shape;

    float m_Speed = 300.0f;
    float m_DirectionX = 0.2f;
    float m_DirectionY = 0.2f;

public:
    Ball(float startX, float startY);
    FloatRect getPosition();
    RectangleShape getShape();
    float getXVelocity();
    void reboundSides();  // will be called from main when a collision is detected with either side of the screen
    void reboundBatOrTop();  // will be called in response to the ball hitting the player's bat or the top of the screen
    void reboundBottom();  // will be called when the ball hits the bottom of the screen.
    void update(Time dt);
};

#endif //PONG_BALL_H
