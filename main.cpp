


#include <iostream>

#include "src/Server.h"
#include "src/Client.h"

using namespace std;


int main() {
    Player * p = new Player;
    World * w = new World{p};


    Client c{p, w};
    c.run();

    delete w;
    delete p;
}
