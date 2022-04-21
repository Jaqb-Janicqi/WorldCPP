#pragma once
#include "Animal.cpp"

class Fox : public Animal {
    int id = 3;
    int strength = 3;
    int initiative = 7;
    char skin = '*';

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