#pragma once
#include "../Organism.cpp"

class Animal : public Organism {
public:
    Animal() : Organism()
    {
        animal = true;
    }

    virtual int randMove()
    {
        int x = 1;
        while (x == 1)
        {
            x = randInt(0, 2);
        }
        return x-1;
    }
    
    virtual Transporter* action(vector<Organism*> &organisms, vector<string> &events)
    {
        if(!inactive)
        {
            if(randInt(0, 1))        // make random move in one direction 
            {
                int moveX = randMove();
                if (!(moveX+posX >= 0 && moveX+posX < worldSizeX-1))
                {
                    action(organisms, events);
                }
                else
                {
                    prevY = posY;
                    prevX = posX;
                    posX += moveX;
                }
            }
            else
            {
                int moveY = randMove();
                if (!(moveY+posY >= 0 && moveY+posY < worldSizeY-1))
                {
                    action(organisms, events);
                }
                else
                {
                    prevY = posY;
                    prevX = posX;
                    posY += moveY;
                }
            }
        }
        else
        {
            prevX = posX;
            prevY = posY;
            inactive = false;
        }
        return NULL;
    }
};