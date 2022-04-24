#pragma once
#include "../RandomFromRange.cpp"
#include "../Global.h"
#include "../Transporter.h"


class Organism {
public:
    int id, strength, initiative, posX, posY, prevX, prevY;
    char skin;
    bool immobile = false;
    bool alive = true;
    bool animal;

    Organism(){}

    virtual int randMove()
    {
        int x = 1;
        while (x == 1)
        {
            x = randInt(0, 2);
        }
        return x-1;
    }
    
    virtual void action()
    {
        if(!immobile)
        {
            if(randInt(0, 1))        // make random move in one direction 
            {
                int moveX = randMove();
                if (!(moveX+posX >= 0 && moveX+posX < worldSizeX-1))
                {
                    action();
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
                    action();
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
            immobile = false;
        }
    }

    virtual Transporter* collision(Organism *enemy, vector<Organism> &organisms)
    {
        if (enemy->id == id)
        {
            int newX, newY, smallerX, smallerY, biggerX, biggerY;
            enemy->immobile = true;
            immobile = true;
            enemy->posX = enemy->prevX;
            enemy->posY = enemy->prevY;

            if(enemy->prevX < posX)
            {
                smallerX = enemy->prevX;
                biggerX = posX;
            }
            else
            {
                smallerX = posX;
                biggerX = enemy->prevX;
            }

            if(enemy->prevY < posY)
            {
                smallerY = enemy->prevY;
                biggerY = posY;
            }
            else
            {
                smallerY = posY;
                biggerY = enemy->prevY;
            }
            
            int freeSpaces = 0;
            int randomIndex;
            vector<int> validIndexes;
            int freeCoordinates[10][2];    // [index][0-y 1-x]

            for (int y = smallerY-1; y <= biggerY+1; y++)       //get coordinates around two organisms
            {
                if(y != smallerY && y != biggerY && y >= 0 && y < worldSizeY) 
                {
                    for (int x = smallerX-1; x <= biggerX+1; x++)
                    {
                        if (x != smallerX && x != biggerX && x >= 0 && x < worldSizeX)
                        {
                            freeCoordinates[freeSpaces][0] = y;
                            freeCoordinates[freeSpaces][1] = x;
                            validIndexes.push_back(freeSpaces);
                            freeSpaces++;
                        }
                    }
                }
            }

            for (int i = 0; i < organisms.size(); i++)      //remove 
            {
                for (int j = 0; j < freeSpaces; j++)
                {
                    if (organisms[i].posY == freeCoordinates[j][0] && organisms[i].posX == freeCoordinates[j][1])
                    {
                        validIndexes.erase(validIndexes.begin() + j);
                        freeSpaces--;
                    }
                }
            }
            validIndexes.shrink_to_fit();

            if (freeSpaces > 1)
            {
                randomIndex = randInt(0, validIndexes.size()-1);
                newY = freeCoordinates[randomIndex][0];
                newX = freeCoordinates[randomIndex][1];
                Transporter *data = new Transporter(id, newX, newY, this->animal);
                return data;
            }
            else if(freeSpaces == 1)
            {
                newY = freeCoordinates[0][0];
                newX = freeCoordinates[0][1];
                Transporter *data = new Transporter(id, newX, newY, this->animal);
                return data;
            }
            else return NULL;
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

    virtual char draw()     //place organism's char in its cell
    {
        return skin;
    }
};