//
// Created by Saqib Bhatti on 15/7/24.
//

#ifndef TWL_ENGINE_H
#define TWL_ENGINE_H


#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Thomas.h"
#include "Bob.h"
#include "LevelManager.h"
#include "SoundManager.h"
#include "HUD.h"


using namespace sf;


class Engine {
private:
    TextureHolder th;

    Thomas m_Thomas;
    Bob m_Bob;

    // A class to manage all the levels
    LevelManager m_LM;

    // Create a SoundManager
    SoundManager m_SM;

    // The Hud
    HUD m_Hud;
    int m_FramesSinceLastHUDUpdate = 0;
    int m_TargetFramesPerHUDUpdate = 500;

    const int TILE_SIZE = 50;
    const int VERTS_IN_QUAD = 4;

    // The force pushing the characters down. representing the number of pixels by which
    //the game characters will be pushed downward each second.
    const int GRAVITY = 300;

    // A regular RenderWindow
    RenderWindow m_Window;


    // The main Views
    View m_MainView;
    View m_LeftView;
    View m_RightView;

    // Three views for the background
    View m_BGMainView;
    View m_BGLeftView;
    View m_BGRightView;

    View m_HudView;

    Sprite m_BackgroundSprite;
    Texture m_BackgroundTexture;

    bool m_Playing = false;

    // Is character 1 or 2 the current focus? When the screen is full screen, should it center on Thomas
    //(m_Character1 = true) or Bob (m_Character1 = false)? Initially, it is
    //initialized to true, to center on Thomas.
    bool m_Character1 = true;

    // Start in full screen (not split) mode
    bool m_SplitScreen = false;

    // Variable holds how much time (in seconds) is remaining to get to the goal of the current level.
    float m_TimeRemaining = 10;
    Time m_GameTimeTotal;

    // Is it time for a new/first level? variable keeps an eye on
    //whether the player has just completed or failed a level.
    bool m_NewLevelRequired = true;

    // The vertex array for the level tiles
    VertexArray m_VALevel;

    // The 2d array with the map for the level. A pointer to a pointer. will hold the two-dimensional
    //array that is returned from the method 'int** nextLevel(VertexArray& rVaLevel)'.
    int** m_ArrayLevel = NULL;

    // Texture for the level tiles
    Texture m_TextureTiles;

    // Private functions for internal use only
    void input();
    void update(float dtAsSeconds);
    void draw();

    // Load a new level
    void loadLevel();

    bool detectCollisions(PlayableCharacter& character);

    // Make a vector of the best places to emit sounds from
    void populateEmitters(vector <Vector2f>& vSoundEmitters, int** arrayLevel);

    // A vector of Vector2f for the fire emitter locations
    vector <Vector2f> m_FireEmitters;

public:
    Engine();

    // Run will call all the private functions
    void run();
};


#endif //TWL_ENGINE_H
