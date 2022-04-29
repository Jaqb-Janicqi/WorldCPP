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
        baseStrength = strength = 5;
        initiative = 4;
        skin = 'H';
    }

    Human() : Animal()
    {
        Human(randInt(0, worldSizeX), randInt(0, worldSizeY));
    }

    Transporter* action(vector<Organism*> &organisms, vector<string> &events)
    {
        bool moved = false, validMove = false;
        unsigned char move = 0;
        int moveX=0, moveY=0;
        
        cout << "You can make your move." << endl;
        if(inactive) inactive = false;
        else
        {
            if(strength == baseStrength) cout << "Potion avaible!" << endl;
            else 
            {
                strength--;
                if(strength == baseStrength) cout << "Potion avaible!" << endl;
                else cout << "You have " << strength << " strength" << endl;
            }
        }

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
                    cerr << "Human was killed by Esc key." << endl;
                    moved = true;
                    validMove = true;
                    system("PAUSE");
                    exit(0);
                    break;
                
                case KEY_SPACEBAR:
                    if(strength <= baseStrength)
                    {
                        strength = 10;
                        move = 0;
                        moveX = 0;
                        moveY = 0;
                        cout << "Potion used! You now have " << strength << " strength!" << endl;
                    }
                    else cout << "You cannot use a potion yet." << endl;
                    break;
                
                case KEY_S:
                    events.push_back("SAVE");
                    validMove = true;
                    moved = true;
                    inactive = true;
                    break;
                
                default:
                    cout << "Invalid move" << endl;
                    move = 0;
                    moveX = 0;
                    moveY = 0;
                    break;
                }
            }

            if(events.size() == 0 || (events.size() > 0 && events.back() != "SAVE"))
            {
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
        }
        system("CLS");
        return NULL;
    }
};