#pragma once
#include "RandomFromRange.cpp"
#include "Transporter.h"


class Organism {
public:
    int id, strength, initiative, posX, posY, prevX, prevY;
    char *occupiedCell;
    char skin;
    bool immobile = false;
    bool alive = true;

    Organism(int id)
    {
        id = id;
        posX = randInt(0, worldSizeX);
        posY = randInt(0, worldSizeY);
        prevX = posX;
        prevY = posY;
    }

    Organism(int id, int x, int y)
    {
        id = id;
        posX = x;
        posY = y;
        prevX = posX;
        prevY = posY;
    }

    int randMove()
    {
        int x = randInt(0, 2);
        return x-1;
    }
    
    void action()
    {
        if(!immobile){
            if(randInt(0, 1))        // make random move in one direction 
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

    Transporter* collision(Organism *enemy)
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
            
            Transporter *data = new Transporter(id, newX, newY);
            return data;
        }
        else
        {
            if (enemy->strength < strength)
            {
                alive = false;
                return NULL;
            }
            else
            {
                enemy->alive = false;
                return NULL;
            }
        }
    }

    void draw()     //place organism's char in its cell
    {
        *occupiedCell = skin;
    }
};