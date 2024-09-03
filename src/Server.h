//

//

#ifndef MARIOCLONE_SERVER_H
#define MARIOCLONE_SERVER_H

#include <SFML/Network.hpp>
#include <unordered_map>
#include <iostream>
#include <string>

#include "settings.h"


using namespace sf;
using namespace std;


struct Connection {
    IpAddress address;
    unsigned short port;

    // player data
    float rotation {};
    int playerNumber {};
    bool canShoot {};
};




class Server {
public:
    Server();

    void run();
    bool initiate();

    void receiveData();
    void sendData(string &, Packet &);
    void sendInitialData(Connection &);
    void sendDataToEveryone(Packet &);

    IpAddress getIP();
    unsigned short serverPort;

private:
    IpAddress serverIp;
    UdpSocket serverSocket;
    unordered_map<string, Connection> connections;
};


#endif //MARIOCLONE_SERVER_H
