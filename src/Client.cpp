//
//
//

#include "Client.h"


Client::Client(Player *& player, World *& world) {
    this->player = player;
    this->world = world;
    this->address = IpAddress::getLocalAddress();

    world->window.create(VideoMode(1200, 800), "Game");
}


void Client::receiveData() {
    Packet p;
    IpAddress sIp;
    unsigned short sP;

    if (socket.receive(p, sIp, sP) == Socket::Done) {
        int header;
        p >> header;

        switch (Settings::PacketTypes(header)) {
            case Settings::PacketTypes::NEW_CONNECTION: {
                string k;
                int num;
                p >> k >> num;
                world->others.push_back(new Player{num});

                break;
            }
            case Settings::PacketTypes::ROTATION_CHANGE: {
                string k;
                float otherRotation;

                p >> k >> otherRotation;
                if (!world->others.empty()) {
                    world->others[0]->barrel.setRotation(otherRotation);
                }

                break;
            }
            case Settings::PacketTypes::PLAYER_SHOOT: {
                std::string k;
                p >> k >> player->canShoot;
                if (player->canShoot) {
                    cout << "YOU CAN SHOOT NOW\n";
                }
                break;
            }
            case Settings::PacketTypes::PROJECTILE_RENDER: {
                std::string k;
                float x, y, angleInRad, initialVelocity;

                p >> k >> x >> y >> angleInRad >> initialVelocity;

                world->projectiles.push_back(Projectile{ x, y, angleInRad, initialVelocity });
                break;
            }
            case Settings::PacketTypes::DISCONNECT: {
                string k;
                p >> k;
                cout << "Player: " << k << " disconnected.\n";
                world->clearWorld();
                break;
            }
            default:
                break;
        }
    }

    p.clear();

    if (!player->canShoot && player->playerHasShot) {
        shoot(player->endOfCannonX, player->endOfCannonY, player->angleInRad, player->power);
    }
}


void Client::shoot(float & x, float & y, float & angleInRad, float & initalVelocity) {
    player->playerHasShot = false;
    Packet p;
    string sender{address.toString() + std::to_string(port)};
    cout << sender << '\n';
    p << Settings::PacketTypes::PLAYER_SHOOT << sender << x << y << angleInRad << initalVelocity;

    if (socket.send(p, serverIp, serverPort) == Socket::Done) {

    }
}



void Client::sendData() {
    string msg;
    Packet p;
    p << Settings::PacketTypes::ROTATION_CHANGE << port << player->barrel.getRotation();

    if (socket.send(p, serverIp, serverPort) == Socket::Done) {

    }
}



void Client::disconnect() {
    Packet p;
    p << Settings::PacketTypes::DISCONNECT << port;

    cout << port << '\n';

    if (socket.send(p, serverIp, serverPort) == Socket::Done) {

    }
    socket.unbind();
    connected = false;
}



void Client::run() {
    Clock clock;
    Time t{sf::Time::Zero};
    Time dt{seconds(1.0f / 60.f)};

    while (world->window.isOpen()) {
        world->processEvents();

        if (world->state == GameState::PLAYING) {
            receiveData();
        }

        if (world->uiw.attemptJoin) {
            attemptJoin();
        }

        t += clock.restart();
        while (t > dt) {
            t -= dt;
            world->processEvents();

            if (world->state == GameState::PLAYING) {
                sendData();
                receiveData();
            }

            world->update(dt.asSeconds());
        }

        if (world->state == GameState::HOSTING) {
            world->update(dt.asSeconds());
        }

        if (((world->state == GameState::WON || world->state == GameState::LOST || !world->window.isOpen()) && connected)) {
            disconnect();
        }

        world->render();
    }
}



void Client::attemptJoin() {
    socket.setBlocking(true);
    serverIp = world->serverIPInput;
    serverPort = stoul(world->serverPortInput);
    port = stoul(world->userPortInput);

    if (socket.bind(port) != Socket::Done) {
        cout << "Unable to bind to port\n";
    }

    Packet p;
    p << Settings::PacketTypes::NEW_CONNECTION << port;

    if (socket.send(p, serverIp, serverPort) != Socket::Done) {
        cout << "Client unable to send initial connection to server." << endl;
    }

    p.clear();

    if (socket.receive(p, serverIp, serverPort) != Socket::Done) {

    }

    p >> player->playerNumber >> player->canShoot;
    player->setPlayerData();

    socket.setBlocking(false);
    p.clear();

    connected = true;

    world->state = GameState::PLAYING;
    world->uiw.attemptJoin = false;
}