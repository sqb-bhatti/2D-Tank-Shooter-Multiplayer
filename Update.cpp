

//
// Created by Saqib Bhatti on 15/7/24.
//

#include <SFML/Graphics.hpp>
#include <sstream>
#include "Engine.h"


using namespace sf;


void Engine::update(float dtAsSeconds) {
    if (m_NewLevelRequired) {
//        m_Thomas.spawn(Vector2f(0,0), GRAVITY);
//        m_Bob.spawn(Vector2f(100, 0), GRAVITY);
//
//        // Make sure spawn is called only once
//        m_TimeRemaining = 10;
//        m_NewLevelRequired = false;

        // Load a level
        loadLevel();
    }

    if (m_Playing) {
        // Update Thomas
        m_Thomas.update(dtAsSeconds);

        // Update Bob
        m_Bob.update(dtAsSeconds);

        // Count down the time the player has left
        m_TimeRemaining -= dtAsSeconds;

        // Have Thomas and Bob run out of time?
        if (m_TimeRemaining <= 0) {
            m_NewLevelRequired = true;
        }
    }

    // Set the appropriate view around the appropriate character
    if (m_SplitScreen) {
        m_LeftView.setCenter(m_Thomas.getCenter());
        m_RightView.setCenter(m_Bob.getCenter());
    } else {
        // Centre full screen around appropriate character
        if (m_Character1) {
            m_MainView.setCenter(m_Thomas.getCenter());
        } else {
            m_MainView.setCenter(m_Bob.getCenter());
        }
    }
}