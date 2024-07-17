//
// Created by Saqib Bhatti on 17/7/24.
//

#ifndef TWL_LEVELMANAGER_H
#define TWL_LEVELMANAGER_H


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TextureHolder.h"
#include <sstream>
#include <fstream>


using namespace sf;
using namespace std;


class LevelManager {
private:
    // hold two integer values that will hold the horizontal and vertical number of tiles that the current map contains.
    Vector2i m_LevelSize;

    Vector2f m_StartPosition;
    float m_TimeModifier = 1;
    float m_BaseTimeLimit = 0;
    int m_CurrentLevel = 0;
    const int NUM_LEVELS = 4;

public:
    // each tile in the sprite-sheet is 50 pixels wide and 50 pixels high.
    const int TILE_SIZE = 50;

    const int VERTS_IN_QUAD = 4;
    float getTimeLimit();
    Vector2f getStartPosition();
    int** nextLevel(VertexArray& rVaLevel);
    Vector2i getLevelSize();
    int getCurrentLevel();
};


#endif //TWL_LEVELMANAGER_H
