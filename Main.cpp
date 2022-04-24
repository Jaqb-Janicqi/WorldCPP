#include <iostream>
#include <conio.h>
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#include "Global.h"
#include "World.cpp"

int worldSizeX, worldSizeY;
int main()
{
    cout << "Please give world dimensions x, y" << endl;
    cin >> worldSizeX >> worldSizeY;
    World world(worldSizeX, worldSizeY);
    world.addOrganism(2, true);
    world.addOrganism(2, true);
    world.addOrganism(2, true);

    char input;
    while (cin.get(input))
    {
        if(input == 's') break;
        world.makeTurn();
    }
        
    return 0;
}