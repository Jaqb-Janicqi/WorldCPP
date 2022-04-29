#pragma once
#include "../RandomFromRange.cpp"
#include "../Transporter.h"


class Organism {
public:
    int id, strength, baseStrength, initiative, posX, posY, prevX, prevY;
    char skin;
    bool inactive = false, alive = true, animal;
    string name;

    Organism(){}
    
    virtual Transporter* action(vector<Organism*> &organisms, vector<string> &events)
    {
        return NULL;
    }

    virtual Transporter* collision(Organism *enemy, vector<Organism*> &organisms, vector<string> &events)
    {
        if (enemy->id == id && enemy->animal == animal)
        {
            int newX, newY, smallerX, smallerY, biggerX, biggerY;
            enemy->inactive = true;
            inactive = true;
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
                    if (organisms[i]->posY == freeCoordinates[j][0] && organisms[i]->posX == freeCoordinates[j][1])
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
                events.push_back("New " + name + " has been spawned!");
                return data;
            }
            else if(freeSpaces == 1)
            {
                newY = freeCoordinates[0][0];
                newX = freeCoordinates[0][1];
                Transporter *data = new Transporter(id, newX, newY, this->animal);
                events.push_back("New " + name + " has been spawned!");
                return data;
            }
            else return NULL;
        }
        else
        {
            if (enemy->strength > strength)
            {
                alive = false;
                events.push_back(name + " has died to " + enemy->name + ".");
                return NULL;
            }
            else
            {
                enemy->alive = false;
                events.push_back(enemy->name + " has died to " + name + ".");
                return NULL;
            }
        }
    }

    virtual char draw()     //return organism's char
    {
        return skin;
    }
};