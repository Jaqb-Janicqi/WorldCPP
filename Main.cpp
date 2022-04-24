#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <stdlib.h> 
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_SPACEBAR 32
#define KEY_ESC 27
#define HUMAN_ID 9999
int worldSizeX, worldSizeY;
#include "RandomFromRange.cpp"
#include "World.cpp"


int main()
{
    cout << "Please give world dimensions x, y" << endl;
    cin >> worldSizeX >> worldSizeY;
    World world(worldSizeX, worldSizeY);
    world.addOrganism(HUMAN_ID, true);
    world.addOrganism(2, true);
    world.addOrganism(5, true);

    while (world.makeTurn()){}
    
    system("pause");
    return 0;
}