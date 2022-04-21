#include <random>
#include <time.h>


class Organism {
    int strength, initiative, posX, posY;
    char *occupiedCell;

    int randMove()
    {
        srand((unsigned) time(NULL)); 
        int x = rand()%3;
        return x-1;
    }

    void action()
    {
        if(rand()%2 > 0)        // make random move in one direction 
        {
            int moveX = randMove();
        }
        else
        {
            int moveY = randMove();
        }
        //TODO
    }

    void collision()
    {}

    void draw()     //place organism's char in its cell
    {}
};