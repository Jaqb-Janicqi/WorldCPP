#pragma once
#include "../Plant.cpp"

class SowThistle : public Plant {
public:
    SowThistle(int x, int y) : Plant()
    {
        posX = x;
        posY = y;
        prevX = posX;
        prevY = posY;
        id = 2;
        baseStrength = strength = 0;
        skin = ',';
        name = "Sow Thistle";
    }

    SowThistle()
    {
        posX = randInt(0, worldSizeX);
        posY = randInt(0, worldSizeY);
        SowThistle(posX, posY);
    }

    Transporter* action(vector<Organism*> &organisms, vector<string> &events)
    {
        for (int i = 0; i < 3; i++) 
        {
            if (randInt(0, 99) < CHANCE_OF_SEWING)
            {
                int freeSpaces = 0, randomIndex, newY, newX;
                vector<int> validIndexes;
                int freeCoordinates[10][2];    // [index][0-y 1-x]

                for (int y = posY-1; y <= posY+1; y++)
                {
                    if(y >= 0 && y < worldSizeY) 
                    {
                        for (int x = posX-1; x <= posX+1; x++)
                        {
                            if (x >= 0 && x < worldSizeX)
                            {
                                freeCoordinates[freeSpaces][0] = y;
                                freeCoordinates[freeSpaces][1] = x;
                                validIndexes.push_back(freeSpaces);
                                freeSpaces++;
                            }
                        }
                    }
                }

                for (int i = 0; i < organisms.size(); i++)
                {
                    for (int j = 0; j < freeSpaces; j++)
                    {
                        if (organisms[i]->posY == freeCoordinates[j][0] && organisms[i]->posX == freeCoordinates[j][1])
                        {
                            validIndexes.erase(validIndexes.begin() + j);
                            freeSpaces--;
                            i = 0;
                            break;
                        }
                    }
                }
                validIndexes.shrink_to_fit();

                if (freeSpaces > 1)
                {
                    randomIndex = randInt(0, validIndexes.size()-1);
                    newY = freeCoordinates[randomIndex][0];
                    newX = freeCoordinates[randomIndex][1];
                    SowThistle *newPlant = new SowThistle(newX, newY);
                    organisms.push_back(newPlant);
                    events.push_back("New " + name + " has sewed!");
                }
                else if(freeSpaces == 1)
                {
                    newY = freeCoordinates[0][0];
                    newX = freeCoordinates[0][1];
                    SowThistle *newPlant = new SowThistle(newX, newY);
                    organisms.push_back(newPlant);
                    events.push_back("New " + name + " has sewed!");
                }
                return NULL;
            }
        }
        return NULL;
    }
};