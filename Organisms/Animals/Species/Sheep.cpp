#pragma once
#include "../Animal.cpp"
#include "../../../Global.h"

class Sheep : public Animal {
public:
    Sheep(int x, int y) : Animal()
    {
        posX = x;
        posY = y;
        prevX = posX;
        prevY = posY;
        id = 2;
        strength = 4;
        initiative = 4;
        skin = 'S';
    }

    Sheep() : Animal()
    {
        posX = randInt(0, worldSizeX);
        posY = randInt(0, worldSizeY);
        prevX = posX;
        prevY = posY;
        id = 2;
        strength = 4;
        initiative = 4;
        skin = 'S';
    }
};