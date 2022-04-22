#pragma once
#include "../Plant.cpp"

class Guarana : public Plant {
public:
    Guarana(int x, int y)
    {
        posX = x;
        posY = y;
        prevX = posX;
        prevY = posY;
        id = 3;
        strength = 0;
        skin = '?';
    }

    Guarana()
    {
        posX = randInt(0, worldSizeX);
        posY = randInt(0, worldSizeY);
        prevX = posX;
        prevY = posY;
        id = 3;
        strength = 0;
        skin = '?';
    }
};