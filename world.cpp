#include <iostream>
#include <vector>
using namespace std;

#include "Organism.cpp"
#include "Plant.cpp"
#include "Animal.cpp"



class World {
private:
    vector<vector<char>> board;
    vector<Organism> organisms;
    int worldSizeX, worldSizeY;
    
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