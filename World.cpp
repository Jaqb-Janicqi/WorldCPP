#include <vector>

#pragma once
#include "Global.h"
#include "RandomFromRange.cpp"
#include "Organisms/Organism.cpp"
#include "Organisms/Animals/Animal.cpp"
#include "Organisms/Animals/Species/Wolf.cpp"
#include "Organisms/Animals/Species/Sheep.cpp"
#include "Organisms/Animals/Species/Fox.cpp"
#include "Organisms/Animals/Species/Turtle.cpp"
#include "Organisms/Animals/Species/Antelope.cpp"
#include "Organisms/Animals/Species/Human.cpp"
#include "Organisms/Plants/Plant.cpp"
#include "Organisms/Plants/Species/Grass.cpp"
#include "Organisms/Plants/Species/SowThistle.cpp"
#include "Organisms/Plants/Species/Guarana.cpp"
#include "Organisms/Plants/Species/Belladona.cpp"
#include "Organisms/Plants/Species/SosnowskyWeed.cpp"


class World {
public:
    World(int x, int y) : ConstWorldSizeX(x), ConstworldSizeY(y){
        board.resize(y , vector<char> (x, ' '));
    }

private:
    const int ConstWorldSizeX, ConstworldSizeY;
    vector<vector<char>> board;
    vector<Organism*> organisms;

    void addOrganism(int orgarnismId, int x, int y, bool animal, bool immobile)
    {
        Organism *newOrganism = NULL;
        if (animal)
        {
            switch (orgarnismId)
            {
            case 0:
                newOrganism = new Human(x, y);
                break;

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
                if (!(organisms[i-1]->initiative < newOrganism->initiative))
                {
                    organisms.insert(organisms.begin() + i, newOrganism);
                    break;
                }
                if (i == 1) organisms.insert(organisms.begin(), newOrganism);
            }
        }
        else organisms.insert(organisms.begin(), newOrganism);
    }

    void removeOrganism(int vectPos)
    {
        delete organisms[vectPos];
        organisms.erase(organisms.begin() + vectPos);
    }

    void drawWorld()
    {
        auto horizLine = []()
        {
            for (int i = 0; i < worldSizeX+2; i++)
            {
                if(i != 0) cout << ' ';
                cout << '=';
            }
            cout << endl;
        };

        for (int y = 0; y < worldSizeY; y++)
        {
            for (int x = 0; x < worldSizeX; x++)
            {
                board[y][x] = ' ';
            }
        }

        for (int i = 0; i < organisms.size(); i++)
        {
            board[organisms[i]->posY][organisms[i]->posX] = organisms[i]->draw();
        }

        system("CLS");
        for (int y = 0; y < worldSizeY; y++)
        {
            if(y == 0) horizLine();

            for (int x = 0; x < worldSizeX; x++)
            {
                if(x == 0) cout << '|' << ' ';
                cout << board[y][x] << ' ';
            }
            cout << '|' << endl;

            if(y == worldSizeY-1) horizLine();
        }
    }

public:
    int makeTurn()
    {
        bool humanAlive = true;

        for (int i = 0; i < organisms.size(); i++)
        {
            if (organisms[i]->id == 0) drawWorld();

            organisms[i]->action();

            for (int j = 0; j < organisms.size(); j++)
            {
                if (i != j && organisms[i]->posX == organisms[j]->posX && organisms[i]->posY == organisms[j]->posY)
                {
                    Transporter *data = organisms[j]->collision(organisms[i], organisms);

                    if (!organisms[i]->alive) 
                    {
                        if(organisms[i]->id == 0) humanAlive = false;
                        removeOrganism(i);
                    }
                    if (!organisms[j]->alive) removeOrganism(j);

                    if (data)
                    {
                        addOrganism(data->id, data->posX, data->posY, data->animal, true);
                    }
                    delete data;
                }
            }
        }

        if (!humanAlive) drawWorld();
        return humanAlive;
    }

    void addOrganism(int orgarnismId, bool animal)
    {
        if(organisms.size() >= worldSizeX*worldSizeY) return;

        int x = randInt(0, worldSizeX-1);
        int y = randInt(0, worldSizeY-1);
        int i = 0;

        while(i < organisms.size())
        {
            if (x == organisms[i]->posX && y == organisms[i]->posY)
            {
                i = 0;
                x = randInt(0, worldSizeX-1);
                y = randInt(0, worldSizeY-1);
            } 
            else i++;
        }

        addOrganism(orgarnismId, x, y, animal, false);
    }    
};