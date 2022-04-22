#pragma once
#include "../Plant.cpp"

class Belladona : public Plant {
public:
    Belladona(int x, int y)
    {
        posX = x;
        posY = y;
        prevX = posX;
        prevY = posY;
        id = 4;
        strength = 99;
        skin = '!';
    }

    Belladona()
    {
        posX = randInt(0, worldSizeX);
        posY = randInt(0, worldSizeY);
        prevX = posX;
        prevY = posY;
        id = 4;
        strength = 99;
        skin = '!';
    }
};