//
// Created by Saqib Bhatti on 16/5/24.
//

#include "Bat.h"


// This the constructor and it is called when we create an object
Bat::Bat(float startX, float startY) {
    m_Position.x = startX;
    m_Position.y = startY;

    m_Shape.setSize(sf::Vector2f(50, 5));
    m_Shape.setFillColor(sf::Color(100, 250, 50));  // set color to green
    m_Shape.setPosition(m_Position);
}


FloatRect Bat::getPosition() {
    return m_Shape.getGlobalBounds();  // The m_Shape.getGlobalBounds line of code returns a FloatRect that is
    // initialized with the coordinates of the four corners of the RectangleShape, that is, m_Shape.
}


RectangleShape Bat::getShape() {
    return m_Shape;
}


void Bat::moveLeft() {
    m_MovingLeft = true;
}

void Bat::moveRight() {
    m_MovingRight = true;
}


void Bat::stopLeft() {
    m_MovingLeft = false;
}


void Bat::stopRight() {
    m_MovingRight = false;
}


void Bat::update(Time dt) {
    if (m_MovingLeft) {
        m_Position.x -= m_Speed * dt.asSeconds(); // The code multiplies the speed by the delta time and then adds or
        // subtracts it from the position.
    }

    if (m_MovingRight) {
        m_Position.x += m_Speed * dt.asSeconds();
    }

    m_Shape.setPosition(m_Position);
}