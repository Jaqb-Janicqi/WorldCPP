#pragma once
#include "../Animal.cpp"
#include "../../../Global.h"


class Wolf : public Animal {
public:
    Wolf(int x, int y) : Animal()
    {
        posX = x;
        posY = y;
        prevX = posX;
        prevY = posY;
        id = 1;
        strength = 9;
        initiative = 5;
        skin = 'W';
    }

    Wolf() : Animal()
    {
        posX = randInt(0, worldSizeX);
        posY = randInt(0, worldSizeY);
        prevX = posX;
        prevY = posY;
        id = 1;
        strength = 9;
        initiative = 5;
        skin = 'W';
    }
};