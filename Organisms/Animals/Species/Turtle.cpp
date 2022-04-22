#pragma once
#include "../Animal.cpp"
#include "../../../RandomFromRange.cpp"
#include "../../../Global.h"

class Turtle : public Animal {
public:
    Turtle(int x, int y)
    {
        posX = x;
        posY = y;
        prevX = posX;
        prevY = posY;
        id = 4;
        strength = 2;
        initiative = 1;
        skin = '@';
    }

    Turtle()
    {
        posX = randInt(0, worldSizeX);
        posY = randInt(0, worldSizeY);
        prevX = posX;
        prevY = posY;
        id = 4;
        strength = 2;
        initiative = 1;
        skin = '@';
    }

    void action()
    {
        if(!immobile && randInt(0,4) == 0)
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

    void collision(Organism *enemy)
    {
        if (enemy->id == id)
        {
            int newX, newY, smallerX, smallerY, biggerX, biggerY;
            enemy->immobile = true;

            if(enemy->posX < posX)
            {
                smallerX = enemy->posX;
                biggerX = posX;
            }
            else
            {
                smallerX = posX;
                biggerX = enemy->posX;
            }

            if(enemy->posY < posY)
            {
                smallerY = enemy->posY;
                biggerY = posY;
            }
            else
            {
                smallerY = posY;
                biggerY = enemy->posY;
            }

            while (!(newX != posX && newX != enemy->posX)) newX = randInt(smallerX-1, biggerX+1);
            while (!(newY != posY && newY != enemy->posY)) newY = randInt(smallerY-1, biggerY+1);
        }
        else
        {
            if (enemy->strength < 5)
            {
                enemy->posX = enemy->prevX;
                enemy->posY = enemy->prevY;
            }
            else
            {
                enemy->alive = false;
            }
        }
    }
};