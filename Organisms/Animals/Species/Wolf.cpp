#pragma once
#include "../Animal.cpp"


class Wolf : public Animal {
public:
    Wolf(int x, int y) : Animal()
    {
        name = "Wolf";
        posX = x;
        posY = y;
        prevX = posX;
        prevY = posY;
        id = 1;
        baseStrength = strength = 9;
        initiative = 5;
        skin = 'W';
    }

    Wolf() : Animal()
    {
        Wolf(randInt(0, worldSizeX), randInt(0, worldSizeY));
    }
};