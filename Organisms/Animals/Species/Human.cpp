#pragma once
#include "../Animal.cpp"


class Human : public Animal {
public:
    Human(int x, int y) : Animal()
    {
        name = "Human";
        posX = x;
        posY = y;
        prevX = posX;
        prevY = posY;
        id = HUMAN_ID;
        strength = 5;
        initiative = 4;
        skin = 'H';
    }

    Human() : Animal()
    {
        Human(randInt(0, worldSizeX), randInt(0, worldSizeY));
    }

    void action(vector<Organism*> &organisms)
    {
        bool moved = false, validMove = false;
        unsigned char move = 0;
        int moveX=0, moveY=0;
        
        cout << "You can make your move." << endl;
        
        while (!moved)
        {
            while (!validMove)
            {
                while (move == 0 || move == 0xE0) move = getch();
                switch (move)
                {
                case KEY_UP:
                    moveY = -1;
                    validMove = true;
                    break;

                case KEY_DOWN:
                    moveY = 1;
                    validMove = true;
                    break;
                    
                case KEY_LEFT:
                    moveX = -1;
                    validMove = true;
                    break;
                    
                case KEY_RIGHT:
                    moveX = 1;
                    validMove = true;
                    break;
                
                case KEY_ESC:
                    alive = false;
                    validMove = true;
                    break;
                
                default:
                    cout << "Invalid move" << endl;
                    move = 0;
                    moveX = 0;
                    moveY = 0;
                    break;
                }
            }

            if (posX+moveX < worldSizeX && posX+moveX >= 0 && posY+moveY < worldSizeY && posY+moveY >= 0)
            {
                moved = true;
                prevX = posX;
                prevY = posY;
                posX += moveX;
                posY += moveY;
            }
            else
            {
                cout << "Invalid move" << endl;
                move = moveX = moveY = 0;
                validMove = false;
            }
        }
        system("CLS");
    }
};