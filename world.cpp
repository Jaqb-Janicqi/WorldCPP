#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

#include "Organism.cpp"
#include "global.h"



class World {
private:
    vector<vector<char>> board;
    vector<Organism> organisms;
    
public:
    World(int x, int y){
        worldSizeX = x;
        worldSizeY = y;
    }

    void makeTurn()
    {

    }

    void drawWorld()
    {

    }
};


int main()
{   
    int x, y;
    cout << "Please give world dimensions x, y" << endl;
    cin >> x >> y;
    World world(x, y);
    return 0;
}