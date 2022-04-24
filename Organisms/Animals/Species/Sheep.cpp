#pragma once
#include "../Animal.cpp"


class Sheep : public Animal {
public:
    Sheep(int x, int y) : Animal()
    {
        name = "Sheep";
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
        Sheep(randInt(0, worldSizeX), randInt(0, worldSizeY));
    }
};