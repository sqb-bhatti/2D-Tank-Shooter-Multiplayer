//
// Created by Saqib Bhatti on 3/9/24.
//

#ifndef MARIOCLONE_PROJECTILE_H
#define MARIOCLONE_PROJECTILE_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#define PI 3.14159265


using namespace sf;

class Projectile {
public:
    Projectile(float, float, float, float);

    void render(RenderWindow &);
    void update(float);

    CircleShape projectile;
    float angle;
    float gravity;
    Vector2f velocity;
    Vector2f position;
};


#endif //MARIOCLONE_PROJECTILE_H
