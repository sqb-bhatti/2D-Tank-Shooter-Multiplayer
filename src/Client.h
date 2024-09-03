//

//

#ifndef MARIOCLONE_CLIENT_H
#define MARIOCLONE_CLIENT_H

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "settings.h"
#include "game/World.h"
#include "game/Player.h"


using namespace sf;
using namespace std;

class Client {
public:
    Client(Player *&, World *&);

    void receiveData();
    void sendData();
    void disconnect();
    void shoot(float &, float &, float &, float &);

    void run();

    void attemptJoin();

private:
    IpAddress serverIp;
    unsigned short serverPort;

    IpAddress address;
    unsigned short port;
    UdpSocket socket;

    Player * player;
    World * world;

    bool connected{false};
};


#endif //MARIOCLONE_CLIENT_H
