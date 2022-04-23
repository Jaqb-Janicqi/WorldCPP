#include <iostream>
using namespace std;
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
    world.addOrganism(2, true);
    world.addOrganism(2, true);
    world.addOrganism(2, true);
    world.addOrganism(1, true);
    world.addOrganism(1, true);
    world.makeTurn();
    return 0;
}