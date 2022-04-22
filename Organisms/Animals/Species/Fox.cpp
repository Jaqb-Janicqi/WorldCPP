#pragma once
#include "../Animal.cpp"

class Fox : public Animal {
public:
    Fox(int x, int y)
    {
        posX = x;
        posY = y;
        prevX = posX;
        prevY = posY;
        id = 3;
        strength = 3;
        initiative = 7;
        skin = '*';
    }

    Fox()
    {
        posX = randInt(0, worldSizeX);
        posY = randInt(0, worldSizeY);
        prevX = posX;
        prevY = posY;
        id = 3;
        strength = 3;
        initiative = 7;
        skin = '*';
    }

    void action()       //TODO will never move into cell occupied by stronger organism
    {
        if(!immobile)
        {
            if(randInt(0, 1))
            {
                int moveX = randMove();
                while (!(moveX+posX >= 0 && moveX+posX < worldSizeX)) moveX = randMove();
                prevX = posX;
                posX += moveX;
                prevY = posY;
            }
            else
            {
                int moveY = randMove();
                while (!(moveY+posY >= 0 && moveY+posY < worldSizeY)) moveY = randMove();
                prevY = posY;
                posY += moveY;
                prevX = posX;
            }
        }
        else
        {
            prevX = posX;
            prevY = posY;
            immobile = false;
        }
    }
};