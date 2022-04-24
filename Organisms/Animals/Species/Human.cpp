#pragma once
#include "../Animal.cpp"
#include "../../../Global.h"

class Human : public Animal {
    Human(int x, int y) : Animal()
    {
        posX = x;
        posY = y;
        prevX = posX;
        prevY = posY;
        id = 0;
        strength = 5;
        initiative = 4;
        skin = 'H';
    }

    Human() : Animal()
    {
        posX = randInt(0, worldSizeX);
        posY = randInt(0, worldSizeY);
        prevX = posX;
        prevY = posY;
        id = 0;
        strength = 5;
        initiative = 4;
        skin = 'H';
    }
};