#pragma once
#include "../Plant.cpp"

class SowThistle : public Plant {
public:
    SowThistle(int x, int y)
    {
        posX = x;
        posY = y;
        prevX = posX;
        prevY = posY;
        id = 2;
        strength = 0;
        skin = ',';
    }

    SowThistle()
    {
        posX = randInt(0, worldSizeX);
        posY = randInt(0, worldSizeY);
        prevX = posX;
        prevY = posY;
        id = 2;
        strength = 0;
        skin = ',';
    }
};