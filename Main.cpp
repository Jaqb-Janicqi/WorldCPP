#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <stdlib.h> 
#include <fstream>
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_SPACEBAR 32
#define KEY_ESC 27
#define KEY_S 115
#define HUMAN_ID 9999
#define CHANCE_OF_SEWING 10         //in %
#define AMOUNT_OF_LINES 3

int worldSizeX, worldSizeY;
#include "RandomFromRange.cpp"
#include "World.cpp"


World* recallState(World *world)
{
    ifstream file;
    file.open("savefile.txt");

    if (!file)
    {                                               
        cerr << "Save file can't be opened or doesn't exist!" << endl;
        system("PAUSE");
    }

    int x, y, amount;
    file >> x >> y >> amount;
    worldSizeX = x;
    worldSizeY = y;

    world = new World(x, y);

    for (int i = 0; i <= amount; i++)
    {
        Organism fromFile;
        file >> fromFile.id >> fromFile.animal >> fromFile.posX >> fromFile.posY >> fromFile.prevX 
            >> fromFile.prevY >> fromFile.strength >> fromFile.baseStrength >> fromFile.inactive >> fromFile.alive;
        
        Organism *newOrganism = world->addOrganism(fromFile.id, fromFile.posX, fromFile.posY, fromFile.animal, fromFile.inactive);
        newOrganism->prevX = fromFile.prevX;
        newOrganism->prevY = fromFile.prevY;
        newOrganism->strength = fromFile.strength;
        newOrganism->baseStrength = fromFile.baseStrength;
        newOrganism->alive = fromFile.alive;
    }
    file.close();

    return world;
}


int main()
{
    bool start = false;
    unsigned char move = 0;
    World *world;

    cout << "Welcome to World by Jakub Janicki!" << endl;
    while (!start)
    {
        cout << "Press space to start a new game" << endl << "Press \'s\' to restore saved game" << endl;
        while (move == 0 || move == 0xE0) move = getch();
        if (move == KEY_SPACEBAR)
        {
            cout << "Please give world dimensions x, y (both bigger than 10)" << endl;
            cin >> worldSizeX >> worldSizeY;
            if(worldSizeX < 10) worldSizeX = 10;
            if(worldSizeY < 10) worldSizeY = 10;
            world = new World(worldSizeX, worldSizeY);
            goto init;
        }
        else if(move == KEY_S)
        {
            world = recallState(world);
            goto play;
        }
        else
        {
            cout << "Bad input" << endl;
            move = 0;
        }
    }

    init: 
    world->addOrganism(HUMAN_ID, true);

    world->addOrganism(1, true);     //add animals
    world->addOrganism(2, true);
    world->addOrganism(3, true);
    world->addOrganism(4, true);
    world->addOrganism(5, true);
    world->addOrganism(1, true);
    world->addOrganism(2, true);
    world->addOrganism(3, true);
    world->addOrganism(4, true);
    world->addOrganism(5, true);
    
    world->addOrganism(1, false);    //add plants
    world->addOrganism(2, false);
    world->addOrganism(3, false);
    world->addOrganism(4, false);
    world->addOrganism(5, false);
    world->addOrganism(1, false);
    world->addOrganism(2, false);
    world->addOrganism(3, false);
    world->addOrganism(4, false);
    world->addOrganism(5, false);

    play:while (world->makeTurn()){}
    
    delete world;
    system("pause");
    return 0;
}