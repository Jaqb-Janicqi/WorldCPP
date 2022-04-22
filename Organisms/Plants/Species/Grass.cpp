#pragma once
#include "../Plant.cpp"

class Grass : public Plant {
public:
    Grass(int x, int y)
    {
        posX = x;
        posY = y;
        prevX = posX;
        prevY = posY;
        id = 1;
        strength = 0;
        skin = '.';
    }

    Grass()
    {
        posX = randInt(0, worldSizeX);
        posY = randInt(0, worldSizeY);
        prevX = posX;
        prevY = posY;
        id = 1;
        strength = 0;
        skin = '.';
    }
};