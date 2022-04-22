#pragma once
#include "../RandomFromRange.cpp"
#include "../Global.h"
#include "../Transporter.h"


class Organism {
public:
    int id, strength, initiative, posX, posY, prevX, prevY;
    char *occupiedCell;
    char skin;
    bool immobile = false;
    bool alive = true;
    bool animal;

    Organism(){}

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

    virtual int randMove()
    {
        int x = randInt(0, 2);
        while (x == 0)
        {
            x = randInt(0, 2);
        }
        return x-1;
    }
    
    virtual void action(vector<vector<char>> &board)
    {
        if(!immobile)
        {
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
        occupiedCell = &board[posY][posX];      //pointer to cell should be an iterator?    //TODO
    }

    virtual Transporter* collision(Organism *enemy, vector<Organism> &organisms)
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
                    }
                }
            }

            if (freeSpaces > 0)
            {
                randomIndex = randInt(0, validIndexes.size()-1);
                newY = freeCoordinates[randomIndex][0];
                newX = freeCoordinates[randomIndex][1];
                Transporter *data = new Transporter(id, newX, newY, animal);
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

    virtual void draw()     //place organism's char in its cell
    {
        *occupiedCell = skin;
    }
};