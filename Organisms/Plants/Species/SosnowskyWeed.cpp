#pragma once
#include "../Plant.cpp"

class SosnowskyWeed : public Plant {
public:
    SosnowskyWeed(int x, int y) : Plant()
    {
        posX = x;
        posY = y;
        prevX = posX;
        prevY = posY;
        id = 5;
        baseStrength = strength = 10;
        skin = '$';
        name = "Sosnowsky Weed";
    }

    SosnowskyWeed()
    {
        posX = randInt(0, worldSizeX);
        posY = randInt(0, worldSizeY);
        SosnowskyWeed(posX, posY);
    }

    Transporter* action(vector<Organism*> &organisms, vector<string> &events)
    {
        for (int i = 0; i < organisms.size(); i++)
        {
            if (organisms[i]->posX >= posX-1 && organisms[i]->posX <= posX+1)
            {
                if (organisms[i]->posY >= posY-1 && organisms[i]->posY <= posY+1)
                {
                    if (organisms[i]->id != id && organisms[i]->animal)
                    {
                        organisms[i]->alive = false;
                        events.push_back(organisms[i]->name + " has been killed by " + name + ".");
                    }
                }
            }
        }

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
                    }
                }
            }
            validIndexes.shrink_to_fit();

            if (freeSpaces > 1)
            {
                randomIndex = randInt(0, validIndexes.size()-1);
                newY = freeCoordinates[randomIndex][0];
                newX = freeCoordinates[randomIndex][1];
                Transporter *data = new Transporter(id, newX, newY, animal);
                events.push_back("New " + name + " has sewed!");
                return data;
            }
            else if(freeSpaces == 1)
            {
                newY = freeCoordinates[0][0];
                newX = freeCoordinates[0][1];
                Transporter *data = new Transporter(id, newX, newY, animal);
                events.push_back("New " + name + " has sewed!");
                return data;
            }
            return NULL;
        }
        else return NULL;
    }
};