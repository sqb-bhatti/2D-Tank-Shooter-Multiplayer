

//
// Created by Saqib Bhatti on 17/7/24.
//


#include "Engine.h"

using namespace sf;
using namespace std;



// The job of the populateEmitters function is to scan through all the elements
//of arrayLevel and decide where to put the emitters. It will store its results in
//m_FireEmitters.
void Engine::populateEmitters(vector <Vector2f>& vSoundEmitters, int** arrayLevel) {
    // Make sure the vector is empty
    vSoundEmitters.empty();

    // Keep track of the previous emitter so we don't make too many
    FloatRect previousEmitter;

    // Search for fire in the level
    for (int x = 0; x < (int)m_LM.getLevelSize().x; x++) {
        for (int y = 0; y < (int)m_LM.getLevelSize().y; y++) {
            if (arrayLevel[y][x] == 2) {  // fire is present
                // Skip over any fire tiles too near a previous emitter.
                /*
                 * The code sets up a nested for loop that loops through arrayLevel, looking
for fire tiles. When it finds one, it makes sure that it does not intersect with
previousEmitter. Only then does it use the pushBack function to add another
emitter to vSoundEmitters.
                 */
                if (!FloatRect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE,
                               TILE_SIZE).intersects(previousEmitter)) {

                    // Add the coordinates of this water block
                    vSoundEmitters.push_back(Vector2f(x * TILE_SIZE, y * TILE_SIZE));

                    // Make a rectangle 6 blocks x 6 blocks, so we don't make any more emitters
                    // too close to this one
                    previousEmitter.left = x * TILE_SIZE;
                    previousEmitter.top = y * TILE_SIZE;
                    previousEmitter.width = TILE_SIZE * 6;
                    previousEmitter.height = TILE_SIZE * 6;
                }
            }
        }
    }
    return;
}