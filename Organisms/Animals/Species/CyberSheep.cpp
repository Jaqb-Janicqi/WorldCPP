#pragma once
#include "../Animal.cpp"

class CyberSheep : public Animal {
public:
    CyberSheep(int x, int y)
    {
        posX = x;
        posY = y;
        prevX = posX;
        prevY = posY;
        id = 6;
        strength = 11;
        initiative = 4;
        skin = '&';
    }

    CyberSheep()
    {
        posX = randInt(0, worldSizeX);
        posY = randInt(0, worldSizeY);
        prevX = posX;
        prevY = posY;
        id = 6;
        strength = 11;
        initiative = 4;
        skin = '&';
    }
    
};