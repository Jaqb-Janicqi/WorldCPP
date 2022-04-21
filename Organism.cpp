#include <random>
#include <time.h>

#pragma once
#include "global.h"
#include "Plant.cpp"
#include "Animal.cpp"


class Organism {
    int strength, initiative, posX, posY;
    char *occupiedCell;

    int randMove()
    {
        srand((unsigned) time(NULL)); 
        int x = rand()%3;
        return x-1;
    }

    void action()
    {
        if(rand()%2 > 0)        // make random move in one direction 
        {
            int moveX = randMove();
            while (!(moveX+posX >= 0 && moveX+posX < worldSizeX)) moveX = randMove();
        }
        else
        {
            int moveY = randMove();
            while (!(moveY+posY >= 0 && moveY+posY < worldSizeY)) moveY = randMove();
        }
        //TODO
    }

    void collision()
    {}

    void draw()     //place organism's char in its cell
    {}
};