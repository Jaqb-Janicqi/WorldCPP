#include <iostream>
using namespace std;

#include "global.h"
#include "World.cpp"

int main()
{
    int x, y;
    cout << "Please give world dimensions x, y" << endl;
    cin >> x >> y;
    World world(x, y);
    return 0;
}