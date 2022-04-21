#pragma once
#include "Animal.cpp"

class Antelope : public Animal {
    int id = 5;
    int strength = 4;
    int initiative = 4;
    char skin = ';';

    virtual void action()
    {
        if(!immobile)
        {
            if(randInt(0, 1))
            {
                int moveX = randMove()*randInt(1, 2);
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

            while (!(newX != posX && newX != enemy->posX)) newX = randInt(smallerX-1, biggerX+1);       //TODO new animal should spawn on empty place
            while (!(newY != posY && newY != enemy->posY)) newY = randInt(smallerY-1, biggerY+1);
            
            Transporter *data = new Transporter(id, newX, newY);
            return data;
        }
        else
        {
            if(randInt(0, 1))   //TODO move to a free cell
            {
                // if(randInt(0, 1))
                // {
                //     int moveX = randMove()*randInt(1, 2);
                //     while (!(moveX+posX >= 0 && moveX+posX < worldSizeX)) moveX = randMove();
                //     prevX = posX;
                //     posX += moveX;
                //     prevY = posY;
                // }
                // else
                // {
                //     int moveY = randMove();
                //     while (!(moveY+posY >= 0 && moveY+posY < worldSizeY)) moveY = randMove();
                //     prevY = posY;
                //     posY += moveY;
                //     prevX = posX;
                // }
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
    }
};