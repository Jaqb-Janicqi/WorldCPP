#include <iostream>
#include <vector>
#include <time.h>
using namespace std;


int randMove(){
    srand((unsigned) time(NULL)); 
    int x = rand()%3;
    return x-1;
}


class Organism {
    int strength, initiative, posX, posY;
    char *occupiedCell;

    void action()
    {
        int moveX = randMove();
        int moveY = randMove();
        while (!(moveX+posX >= 0 && moveX+posX < World::worldSizeX)) moveX = randMove();
        while (!(moveY+posY >= 0 && moveY+posY < World::worldSizeY)) moveY = randMove();
        //TODO
    }

    void collision()
    {}

    void draw()     //place organism's char in its cell
    {}
};


class Plant : Organism {

};


class Animal : Organism {

};


static class World {
private:
    vector<vector<char>> board;
    vector<Organism> organisms;
    
public:
    static int worldSizeX, worldSizeY;
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