//

//

#include "Server.h"


Server::Server() {
    serverSocket.setBlocking(false);
    serverIp = IpAddress::getLocalAddress();
}


void Server::run() {
    receiveData();
}


void Server::receiveData() {
    Packet packet;
    IpAddress senderIp;
    int header;

    packet.clear();

    if (serverSocket.receive(packet, senderIp, serverPort) == Socket::Done) {
        packet >> header;

        switch (Settings::PacketTypes(header)) {
            case Settings::PacketTypes::NEW_CONNECTION: {
                if (connections.size() == 2) {
                    cout << "Player tried connecting - game lobby is full.\n";
                } else {
                    if (connections.empty()) {
                        cout << "Player 1 Connecting\n";

                        int playerOneNumber { 1 };
                        unsigned short senderPort;

                        packet >> senderPort;

                        Connection c;
                        c.address = senderIp;
                        c.port = senderPort;
                        c.canShoot = true;
                        c.playerNumber = playerOneNumber;

                        connections[senderIp.toString() + to_string(senderPort)] = c;
                        packet.clear();
                        packet << playerOneNumber << c.canShoot;

                        if (serverSocket.send(packet, senderIp, senderPort) == Socket::Done) {
                            cout << "Sent player 1 initial data.\n";

                            cout << "Made new connection with: " << senderIp << c.port << '\n';
                            cout << "Total connections: " << connections.size() << '\n';
                        } else {
                            cout << "Player 2 Connecting\n";

                            unsigned short senderPort;
                            int playerTwoNumber { 2 };
                            packet >> senderPort;

                            Connection c;
                            c.address = senderIp;
                            c.port = senderPort;
                            c.canShoot = false;
                            c.playerNumber = playerTwoNumber;

                            packet.clear();

                            packet << playerTwoNumber << c.canShoot;

                            if (serverSocket.send(packet, senderIp, senderPort) == Socket::Done) {
                                cout << "Sent player 2 initial data.\n";
                            }

                            packet.clear();

                            sendInitialData(c);
                            string sender{senderIp.toString() + to_string(senderPort)};
                            connections[sender] = c;

                            cout << "Made new connection with: " << senderIp << c.port << '\n';
                            cout << "Total connections: " << connections.size() << '\n';

                            packet.clear();

                            packet << Settings::PacketTypes::NEW_CONNECTION << sender << c.playerNumber;
                            sendData(sender, packet);
                            packet.clear();
                        }
                    }

                    break;
                }

                case Settings::PacketTypes::ROTATION_CHANGE: {
                    float rotation;
                    unsigned short senderPort;

                    packet >> senderPort >> rotation;

                    string sender(senderIp.toString() + to_string(senderPort));
                    if (connections.contains(sender)) {
                        connections[sender].rotation = rotation;

                        Packet toSendPacket;
                        toSendPacket << Settings::PacketTypes::ROTATION_CHANGE << sender << rotation;

                        sendData(sender, toSendPacket);
                    }
                    break;
                }
                case Settings::PacketTypes::PLAYER_SHOOT: {
                    string sender;
                    float x, y, angleInRad, initalVelocity;
                    bool canShoot = true;

                    packet >> sender >> x >> y >> angleInRad >> initalVelocity;
                    cout << sender << " has shot.\n";
                    packet.clear();

                    packet << Settings::PacketTypes::PROJECTILE_RENDER << sender << x << y << angleInRad << initalVelocity;
                    sendDataToEveryone(packet);

                    packet.clear();
                    packet << Settings::PacketTypes::PLAYER_SHOOT << sender << canShoot;
                    sendData(sender, packet);
                    break;
                }
                case Settings::PacketTypes::DISCONNECT: {
                    cout << "Player disconnected\n";
                    unsigned short senderPort;

                    packet >> senderPort;

                    string sender(std::string(senderIp.toString() + std::to_string(senderPort)));
                    Packet toSendPacket;
                    toSendPacket << Settings::DISCONNECT << sender;

                    sendData(sender, toSendPacket);

                    connections.erase(sender);
                    cout << "Total connections: " << connections.size() << '\n';

                    break;
                }
                default:
                    break;
            }
        }
        packet.clear();
    }
}



void Server::sendData(string & sender, Packet & p) {
    for (const auto & [key, val] : connections) {
        if (key != sender) {
            if (serverSocket.send(p, val.address, val.port) == Socket::Done) {

            }
        }
    }
}



void Server::sendDataToEveryone(Packet & p) {
    for (const auto & [key, val] : connections) {
        if (serverSocket.send(p, val.address, val.port) == Socket::Done) {

        }
    }
}



void Server::sendInitialData(Connection & c) {
    Packet p;

    for (const auto & [key, val] : connections) {
        p << Settings::PacketTypes::NEW_CONNECTION << key << val.playerNumber;

        if (serverSocket.send(p, c.address, c.port) == Socket::Done) {

        }
        p.clear();
    }
}


IpAddress Server::getIP() {
    return serverIp;
}



bool Server::initiate() {
    if (serverSocket.bind(serverPort) != Socket::Done) {
        cout << "Could not bind server socket to given port: " << serverPort << '\n';
        return false;
    }

    serverSocket.setBlocking(false);
    return true;
}