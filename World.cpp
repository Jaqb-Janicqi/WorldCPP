#pragma once
#include "Coordinates.h"
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
private:
    const int ConstWorldSizeX, ConstworldSizeY;
    vector<Coordinates> spawnProtect;
    vector<vector<char>> board;
    vector<Organism*> organisms;
    vector<string> events;

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

        system("CLS");

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

        cout << "Now the world looks like this:" << endl;

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

        for (int i = 0; i < AMOUNT_OF_LINES && events.size() > 0; i++)
        {
            cout << events.back() << endl;
            events.pop_back();
        }
        horizLine();
        events.clear();
        
    }

    void saveState()
    {
        for (int i = 0; i < organisms.size(); i++)
        {
            organisms[i]->inactive = true;
            if(organisms[i]->id != HUMAN_ID) break;
        }
        
        ofstream("savefile.txt");
        ofstream file;
        file.open("savefile.txt");

        file << worldSizeX << ' ' << worldSizeY << ' ' << organisms.size() << endl;

        for (int i = 0; i < organisms.size(); i++)
        {
            file << organisms[i]->id << ' ' << organisms[i]->animal << ' ' << organisms[i]->posX << ' ' << organisms[i]->posY << ' '
                    << organisms[i]->prevX << ' ' << organisms[i]->prevY << ' ' << organisms[i]->strength << ' '
                    << organisms[i]->baseStrength << ' ' << organisms[i]->inactive << ' ' << organisms[i]->alive 
            << endl;
        }

        file.close();
        events.pop_back();
    }

public:
    World(int x, int y) : ConstWorldSizeX(x), ConstworldSizeY(y)    {
        board.resize(y , vector<char> (x, ' '));
    }

    bool makeTurn()
    {
        if(spawnProtect.size() > 0) spawnProtect.clear();
        bool keepRunning = true;
        Transporter *data = NULL;

        for (int i = 0; i < organisms.size(); i++)
        {
            start: if (organisms[i]->id == HUMAN_ID) drawWorld();

            data = organisms[i]->action(organisms, events);
            if(data) 
            {
                addOrganism(data->id, data->posX, data->posY, data->animal, true);
                data = NULL;
            }

            if(events.size() > 0 && events.back() == "SAVE") 
            {
                saveState();
                goto start;
            }

            for (int j = 0; j < organisms.size(); j++)
            {
                if (organisms[i]->alive && organisms[j]->alive)
                {
                    if (i != j && organisms[i]->posX == organisms[j]->posX && organisms[i]->posY == organisms[j]->posY)
                    {
                        data = organisms[j]->collision(organisms[i], organisms, events);

                        if (data)
                        {
                            addOrganism(data->id, data->posX, data->posY, data->animal, true);
                        }
                        delete data;
                    }
                }
            }
            for (int k = organisms.size()-1; k >= 0; k--)
            {
                if(organisms[k]->alive == false) 
                {
                    if(organisms[k]->id == HUMAN_ID) keepRunning = false;
                    delete organisms[k];
                    organisms.erase(organisms.begin() + k);
                }
            }
        }

        if (organisms.size() <= 1) keepRunning = false;       

        if (!keepRunning) 
        {
            drawWorld();
            cerr << "Human died." << endl;
            system("PAUSE");
        }
        return keepRunning;
    }

    Organism* addOrganism(int orgarnismId, int x, int y, bool animal, bool inactive)
    {
        Organism *newOrganism = NULL;
        if (animal)
        {
            switch (orgarnismId)
            {
            case HUMAN_ID:
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
        return newOrganism;
    }

    void addOrganism(int orgarnismId, bool animal)
    {
        if(organisms.size() >= worldSizeX*worldSizeY) return;

        int x = randInt(0, worldSizeX-1);
        int y = randInt(0, worldSizeY-1);
        int i = 0;

        if(orgarnismId == HUMAN_ID && animal == true)
        {
            int index = 0;
            for (int j = -1; j <= 1; j++)
            {
                for (int k = -1; k <= 1; k++)
                {
                    spawnProtect.push_back(Coordinates(y+j, x+k));
                    index++;
                }
            }
        }

        if(organisms.size() >= worldSizeX*worldSizeY-spawnProtect.size()) return;

        while(i < organisms.size())
        {
            auto rollNew = [&]()
            {
                x = randInt(0, worldSizeX-1);
                y = randInt(0, worldSizeY-1);
            };

            if(spawnProtect.size() > 0)
            {
                for (int j = 0; j < spawnProtect.size(); j++)
                {
                    if (x == spawnProtect[i].x && y == spawnProtect[i].y)
                    {
                        i = j = 0;
                        rollNew();
                        break;
                    }
                }
            }

            if (x == organisms[i]->posX && y == organisms[i]->posY)
            {
                i = 0;
                rollNew();
            } 
            else i++;
        }

        addOrganism(orgarnismId, x, y, animal, false);
    }
};