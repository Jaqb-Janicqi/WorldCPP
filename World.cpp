#include <vector>

#pragma once
#include "global.h"
#include "RandomFromRange.cpp"
#include "Organisms/Organism.cpp"
#include "Organisms/Animals/Animal.cpp"
#include "Organisms/Animals/Species/Wolf.cpp"
#include "Organisms/Animals/Species/Sheep.cpp"
#include "Organisms/Animals/Species/Fox.cpp"
#include "Organisms/Animals/Species/Turtle.cpp"
#include "Organisms/Animals/Species/Antelope.cpp"
#include "Organisms/Animals/Species/CyberSheep.cpp"
#include "Organisms/Animals/Species/Human.cpp"
#include "Organisms/Plants/Plant.cpp"
#include "Organisms/Plants/Species/Grass.cpp"
#include "Organisms/Plants/Species/SowThistle.cpp"
#include "Organisms/Plants/Species/Guarana.cpp"
#include "Organisms/Plants/Species/Belladona.cpp"
#include "Organisms/Plants/Species/SosnowskyWeed.cpp"


class World {
public:
    vector<Organism> organisms;
    const int worldSizeX, worldSizeY;
    World(int x, int y) : worldSizeX(x), worldSizeY(y){}

    void addOrganism(int orgarnismId, int x, int y, bool animal)
    {
        Organism *newOrganism = NULL;
        if (animal)
        {
            switch (orgarnismId)
            {
            case 1:
                newOrganism = new Wolf(x, y);
                break;

            case 2:
                newOrganism = new Sheep(x, y);
                break;

            case 3:
                newOrganism = new Fox(x, y);
                break;

            case 4:
                newOrganism = new Turtle(x, y);
                break;

            case 5:
                newOrganism = new Antelope(x, y);
                break;

            case 6:
                newOrganism = new CyberSheep(x, y);
                break;
            
            default:
                break;
            }
        }
        else
        {
            switch (orgarnismId)
            {
            case 1:
                newOrganism = new Grass(x, y);
                break;

            case 2:
                newOrganism = new SowThistle(x, y);
                break;

            case 3:
                newOrganism = new Guarana(x, y);
                break;

            case 4:
                newOrganism = new Belladona(x, y);
                break;

            case 5:
                newOrganism = new SosnowskyWeed(x, y);
                break;
            
            default:
                break;
            }
        }

        if(organisms.size() >= 1)       //mainains a sorted vector of organisms (youngest organisms inserted at last pos of given initiative)
        {
            for (int i = organisms.size(); i >= 1; i--)
            {
                if (!(organisms[i-1].initiative < newOrganism->initiative))
                {
                    organisms.insert(organisms.begin() + i, *newOrganism);
                    break;
                }
                if (i == 1) organisms.insert(organisms.begin(), *newOrganism);
            }
        }
        else organisms.insert(organisms.begin(), *newOrganism);

        delete newOrganism;
        
    }

    void removeOrganism(int vectPos)
    {
        organisms.erase(organisms.begin() + vectPos);
    }

private:
    vector<vector<char>> board;

    void makeTurn()
    {
        for (int i = 0; i < organisms.size(); i++)
        {
            if (organisms[i].id == 0) drawWorld();
            organisms[i].action();
            for (int j = 0; j < organisms.size(); j++)
            {
                if (organisms[i].posX == organisms[j].posX && organisms[i].posY == organisms[j].posY)
                {
                    organisms[j].collision(&organisms[i]);

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
};