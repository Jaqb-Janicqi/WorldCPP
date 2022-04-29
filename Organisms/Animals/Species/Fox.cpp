#pragma once
#include "../Animal.cpp"


class Fox : public Animal {
public:
    Fox(int x, int y) : Animal()
    {
        name = "Fox";
        posX = x;
        posY = y;
        prevX = posX;
        prevY = posY;
        id = 3;
        baseStrength = strength = 3;
        initiative = 7;
        skin = 'F';
    }

    Fox() : Animal()
    {
        Fox(randInt(0, worldSizeX), randInt(0, worldSizeY));
    }

    Transporter* action(vector<Organism*> &organisms, vector<string> &events)
    {
        if(!inactive)
        {
            vector<Coordinates> freeSpaces;
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    int cellx = j+posX, celly = i+posY;
                    if ((i == 0 || j == 0) && !(j == 0 && i == 0) && cellx < worldSizeX && cellx >=0 && celly < worldSizeY && celly >= 0)
                    {
                        for (int k = 0; k < organisms.size(); k++)
                        {
                            if(!(organisms[k]->posX == cellx && organisms[k]->posY == celly) || !organisms[k]->alive)
                            {
                                if(organisms[k]->strength <= strength || !organisms[k]->alive) freeSpaces.push_back(Coordinates(celly, cellx));
                            }
                        }
                    }
                }
            }

            if (freeSpaces.size() > 0)
            {
                int randomIndex;
                if(freeSpaces.size() == 1) randomIndex = 0;
                else randomIndex = randInt(0, freeSpaces.size()-1);

                prevX = posX;
                prevY = posY;
                posX = freeSpaces[randomIndex].x;
                posY = freeSpaces[randomIndex].y;
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