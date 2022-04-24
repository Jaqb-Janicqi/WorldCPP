#include <iostream>
#include <conio.h>
#include <string>
#include <stdlib.h> 
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_SPACEBAR 32
#define KEY_ESC 27

#include "Global.h"
#include "World.cpp"

int worldSizeX, worldSizeY;

int main()
{
    cout << "Please give world dimensions x, y" << endl;
    cin >> worldSizeX >> worldSizeY;
    World world(worldSizeX, worldSizeY);
    world.addOrganism(0, true);
    world.addOrganism(2, true);
    world.addOrganism(2, true);
    world.addOrganism(1, true);

    while (world.makeTurn()){}
    
    system("pause");
    return 0;
}