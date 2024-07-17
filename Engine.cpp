//
// Created by Saqib Bhatti on 15/7/24.
//

#include "Engine.h"


Engine::Engine() {
    // Get the screen resolution and create an SFML window and View
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    // Create a video mode object
    VideoMode vm(resolution.x, resolution.y);

    // Create and open a window for the game
    m_Window.create(vm, "Thomas was late");


    // Initialize the full screen view
    m_MainView.setSize(resolution);
    m_HudView.reset(FloatRect(0, 0, resolution.x, resolution.y));

    // Initialize the split-screen Views. The setViewport function assigns a portion of the screen to an SFML
    //View object. It doesn't work with pixel coordinates, however. It works using a ratio.
    m_LeftView.setViewport(FloatRect(0.001f, 0.001f, 0.498f, 0.998f));

    m_RightView.setViewport(FloatRect(0.5f, 0.001f, 0.499f, 0.998f));

    m_BGLeftView.setViewport(FloatRect(0.001f, 0.001f, 0.498f, 0.998f));

    m_BGRightView.setViewport(FloatRect(0.5f, 0.001f, 0.499f, 0.998f));

    m_BackgroundTexture = TextureHolder::GetTexture("graphics/background.png");

    // Associate the sprite with the texture
    m_BackgroundSprite.setTexture(m_BackgroundTexture);

    // Load the texture for the background vertex array
    m_TextureTiles = TextureHolder::GetTexture("graphics/tiles_sheet.png");
}


void Engine::run() {
    // Timing
    Clock clock;

    while (m_Window.isOpen()) {
        Time dt = clock.restart();

        // Update the total game time
        m_GameTimeTotal += dt;

        // Make a decimal fraction from the delta time
        float dtAsSeconds = dt.asSeconds();

        // Call each part of the game loop in turn
        input();
        update(dtAsSeconds);
        draw();
    }
}