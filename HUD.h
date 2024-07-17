//
// Created by Saqib Bhatti on 17/7/24.
//

#ifndef TWL_HUD_H
#define TWL_HUD_H


#include <SFML/Graphics.hpp>


using namespace sf;

class HUD {
private:
    Font m_Font;
    Text m_StartText;
    Text m_TimeText;
    Text m_LevelText;

public:
    HUD();
    Text getMessage();
    Text getLevel();
    Text getTime();
    void setLevel(String text);
    void setTime(String text);

};


#endif //TWL_HUD_H
