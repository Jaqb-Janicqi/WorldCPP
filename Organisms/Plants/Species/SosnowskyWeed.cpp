#pragma once
#include "../Plant.cpp"

class SosnowskyWeed : public Plant {
public:
    SosnowskyWeed(int x, int y)
    {
        posX = x;
        posY = y;
        prevX = posX;
        prevY = posY;
        id = 5;
        strength = 10;
        skin = '$';
    }

    SosnowskyWeed()
    {
        posX = randInt(0, worldSizeX);
        posY = randInt(0, worldSizeY);
        prevX = posX;
        prevY = posY;
        id = 5;
        strength = 10;
        skin = '$';
    }
};