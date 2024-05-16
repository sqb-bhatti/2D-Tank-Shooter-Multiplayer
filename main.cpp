


#include <sstream>  // the sstream class adds some really useful functionality for combining Strings and other
// variable types into a String.
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Bat.h"


using namespace std;



int main() {
    // Create a video mode object
    VideoMode vm(1920, 1080);

    // Create and open a window for the game
    RenderWindow window(vm, "Pong");

    int score = 0;
    int lives = 3;

    // Create a bat at the bottom center of the screen
    Bat bat(1920 / 2, 1080 - 150);

    // Create a Text object called HUD
    Text hud;

    // A cool retro-style font
    Font font;
    font.loadFromFile("fonts/DS-DIGI.ttf");

    // Set the font to our retro-style
    hud.setFont(font);

    // Make it nice and big
    hud.setCharacterSize(75);

    // Choose a color
    hud.setFillColor(Color::White);

    hud.setPosition(20, 20);

    // Here is our clock for timing everything
    Clock clock;



    while (window.isOpen()) {

        /*
         ****************************************
         Handle the players input
         ****************************************
         */
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            // Handle the player quitting
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                window.close();
            }

            // Handle the pressing and releasing of the arrow keys
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                bat.moveLeft();
            } else {
                bat.stopLeft();
            }

            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                bat.moveRight();
            } else {
                bat.stopRight();
            }

        }

        /*
        ****************************************
        Update the bat, the ball and the HUD
        ****************************************
        */
        // Update the delta time
        Time dt = clock.restart();
        bat.update(dt);  // call update on the Bat instance and pass in the delta time. when the Bat class receives
        // the delta time, it will use the value to move the bat based on the previously received movement instructions
        // from the player and the desired speed of the bat.

        // Update the HUD text
        stringstream ss;
        ss << "Score:" << score << "    Lives:" << lives;
        hud.setString(ss.str());



        /*
        ****************************************
        Draw the bat, the ball and the HUD
        ****************************************
        */
        window.clear();
//        window.draw(m_Shape);
        window.draw(hud);
        window.draw(bat.getShape());
        window.display();
    }
    return 0;
}
