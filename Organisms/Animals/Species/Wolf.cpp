#pragma once
#include "../Animal.cpp"


class Wolf : public Animal {
public:
    Wolf(int x, int y)
    {
        posX = x;
        posY = y;
        prevX = posX;
        prevY = posY;
        id = 1;
        strength = 9;
        initiative = 5;
        skin = '#';
    }

    Wolf()
    {
        posX = randInt(0, worldSizeX);
        posY = randInt(0, worldSizeY);
        prevX = posX;
        prevY = posY;
        id = 1;
        strength = 9;
        initiative = 5;
        skin = '#';
    }
};