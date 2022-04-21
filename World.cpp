#include <vector>

#pragma once
#include "global.h"
#include "RandomFromRange.cpp"
#include "Organism.cpp"
#include "Plant.cpp"
#include "Animal.cpp"
#include "Wolf.cpp"
#include "Sheep.cpp"
#include "Fox.cpp"
#include "Turtle.cpp"
#include "Antelope.cpp"
#include "CyberSheep.cpp"
#include "Grass.cpp"
#include "SowThistle.cpp"
#include "Guarana.cpp"
#include "Belladona.cpp"
#include "SosnowskyWeed.cpp"


class World {
private:
    vector<vector<char>> board;
    vector<Organism> organisms;

    void addOrganism(int orgarnismId, int x, int y)
    {
        switch (orgarnismId)
        {
        case 1:
            /* code */
            break;
        
        default:
            break;
        }
        
    }

    void removeOrganism(int vectPos)
    {
        organisms.erase(organisms.begin() + vectPos);
    }

    void makeTurn()
    {
        for (int i = 0; i < organisms.size(); i++)
        {
            organisms[i].action();
            for (int j = 0; j < organisms.size(); j++)
            {
                if (organisms[i].posX == organisms[j].posX && organisms[i].posY == organisms[j].posY)
                {
                    Transporter *data = organisms[i].collision(&organisms[j]);
                    if (data)
                    {
                        addOrganism(data->id, data->posX, data->posY);
                        delete data;
                    }

                    if (!organisms[i].alive)
                    {
                        removeOrganism(i);
                    }
                    if (!organisms[j].alive)
                    {
                        removeOrganism(j);
                    }
                }
            }
        }
    }

    void drawWorld()
    {
        for (int y = 0; y < worldSizeY; y++)
        {
            for (int x = 0; x < worldSizeX; x++)
            {
                board[y][x] = ' ';
            }
        }

        for (int i = 0; i < organisms.size(); i++)
        {
            organisms[i].draw();
        }
        
        for (int y = 0; y < worldSizeY; y++)
        {
            for (int x = 0; x < worldSizeX; x++)
            {
                cout << board[y][x];
            }
            cout << endl;
        }
    }
    
public:
    const int worldSizeX, worldSizeY;
    World(int x, int y) : worldSizeX(x), worldSizeY(y){}
};