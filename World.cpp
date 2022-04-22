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
        Organism *newOrganism;
        if (animal)
        {
            switch (orgarnismId)
            {
            case 1:
                newOrganism = new Wolf(x, y);
                break;

            case 2:
                /* code */
                break;

            case 3:
                /* code */
                break;

            case 4:
                /* code */
                break;

            case 5:
                /* code */
                break;

            case 6:
                /* code */
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
                /* code */
                break;

            case 2:
                /* code */
                break;

            case 3:
                /* code */
                break;

            case 4:
                /* code */
                break;

            case 5:
                /* code */
                break;
            
            default:
                break;
            }
        }
        
        
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
            organisms[i].action(this);
            for (int j = 0; j < organisms.size(); j++)
            {
                if (organisms[i].posX == organisms[j].posX && organisms[i].posY == organisms[j].posY)
                {
                    organisms[j].collision(&organisms[i], this);

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