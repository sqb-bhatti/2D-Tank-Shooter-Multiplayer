//
// Created by Saqib Bhatti on 16/5/24.
//

#include "Ball.h"


using namespace sf;


// This the constructor function
Ball::Ball(float startX, float startY) {
    m_Position.x = startX;
    m_Position.y = startY;

    m_Shape.setSize(Vector2f(10, 10));
    m_Shape.setPosition(m_Position);
}


FloatRect Ball::getPosition() {
    return m_Shape.getGlobalBounds();
}


// The getShape function returns m_Shape so that it can be drawn each frame of the game loop.
RectangleShape Ball::getShape() {
    return m_Shape;
}


// The getXVelocity function tells the main function which direction the ball is traveling in
float Ball::getXVelocity() {
    return m_DirectionX;
}


// In the reboundSides function, m_DirectionX has its value inverted, which will have the effect of making a positive
// value negative and a negative value positive, thereby reversing (horizontally) the direction the ball is traveling in
void Ball::reboundSides() {
    m_DirectionX = -m_DirectionX;
}


// reboundBatOrTop does exactly the same but with m_DirectionY, which has the effect of reversing the direction
// the ball is traveling in vertically.
void Ball::reboundBatOrTop() {
    m_DirectionY = -m_DirectionY;
}


// The reboundBottom function repositions the ball at the top center of the screen and sends it downward. This is just
// what we want after the player has missed a ball and it has hit the bottom of the screen.
void Ball::reboundBottom() {
    m_Position.y = 0;
    m_Position.x = 500;
    m_DirectionY = -m_DirectionY;
}


// The newly updated m_Position values are then used to change the position the m_Shape RectangleShape
// instance is positioned at.
void Ball::update(Time dt) {
    // Update the ball's position
    m_Position.y += m_DirectionY * m_Speed * dt.asSeconds();
    m_Position.x += m_DirectionX * m_Speed * dt.asSeconds();

    // Move the ball
    m_Shape.setPosition(m_Position);
}