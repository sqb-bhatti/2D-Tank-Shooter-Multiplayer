//
// Created by Saqib Bhatti on 3/9/24.
//

#ifndef MARIOCLONE_SETTINGS_H
#define MARIOCLONE_SETTINGS_H


namespace Settings {
    enum PacketTypes : int {
        NEW_CONNECTION = 1,
        ROTATION_CHANGE = 2,
        PLAYER_SHOOT = 3,
        PROJECTILE_RENDER = 4,
        DISCONNECT = 5
    };
}



#endif //MARIOCLONE_SETTINGS_H
