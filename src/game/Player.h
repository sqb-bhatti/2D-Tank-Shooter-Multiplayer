//
//
//

#ifndef MARIOCLONE_PLAYER_H
#define MARIOCLONE_PLAYER_H


#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

#include "Projectile.h"


using namespace sf;
using namespace std;

#define PI 3.14159265

class Player {
public:
    Player();
    Player(int);
    void update(float, sf::RenderWindow &);
    void render(sf::RenderWindow &);
    void shoot();
    void setPlayerData();

    Texture texture;
    Sprite body;
    Sprite barrel;

    float calculationAngle;
    float initialAngle;
    float upperBoundAngle;
    float lowerBoundAngle;

    bool canShoot{false};
    bool playerHasShot{false};
    bool alive{true};

    int playerNumber;
    Vector2f position;

    float angleInRad;
    float endOfCannonX;
    float endOfCannonY;
    float initialVelocity{ 15.f };

    float power{ 0.f };

    vector<Projectile> projectiles;
};


#endif //MARIOCLONE_PLAYER_H
