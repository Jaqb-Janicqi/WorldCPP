#pragma once
#include "../Plant.cpp"

class Belladona : public Plant {
public:
    Belladona(int x, int y) : Plant()
    {
        posX = x;
        posY = y;
        prevX = posX;
        prevY = posY;
        id = 4;
        baseStrength = strength = 99;
        skin = 'B';
        name = "Belladona";
    }

    Belladona()
    {
        posX = randInt(0, worldSizeX);
        posY = randInt(0, worldSizeY);
        Belladona(posX, posY);
    }
};