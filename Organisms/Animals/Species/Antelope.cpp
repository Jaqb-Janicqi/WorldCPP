#pragma once
#include "../Animal.cpp"


class Antelope : public Animal {
public:
    Antelope(int x, int y) : Animal()
    {
        name = "Antelope";
        posX = x;
        posY = y;
        prevX = posX;
        prevY = posY;
        id = 5;
        strength = 4;
        initiative = 4;
        skin = 'A';
    }

    Antelope() : Animal()
    {
        Antelope(randInt(0, worldSizeX), randInt(0, worldSizeY));
    }

    void action(vector<Organism*> &organisms)
    {
        if(!immobile)
        {
            if(randInt(0, 1))
            {
                int moveX = randMove()*randInt(1, 2);
                while (!(moveX+posX >= 0 && moveX+posX < worldSizeX)) moveX = randMove();
                prevX = posX;
                posX += moveX;
                prevY = posY;
            }
            else
            {
                int moveY = randMove();
                while (!(moveY+posY >= 0 && moveY+posY < worldSizeY)) moveY = randMove();
                prevY = posY;
                posY += moveY;
                prevX = posX;
            }
        }
        else
        {
            prevX = posX;
            prevY = posY;
            immobile = false;
        }
    }

    virtual Transporter* collision(Organism *enemy, vector<Organism*> &organisms)
    {
        if (enemy->id == id && enemy->animal == animal)
        {
            int newX, newY, smallerX, smallerY, biggerX, biggerY;
            enemy->immobile = true;
            immobile = true;
            enemy->posX = enemy->prevX;
            enemy->posY = enemy->prevY;

            if(enemy->prevX < posX)
            {
                smallerX = enemy->prevX;
                biggerX = posX;
            }
            else
            {
                smallerX = posX;
                biggerX = enemy->prevX;
            }

            if(enemy->prevY < posY)
            {
                smallerY = enemy->prevY;
                biggerY = posY;
            }
            else
            {
                smallerY = posY;
                biggerY = enemy->prevY;
            }
            
            int freeSpaces = 0;
            int randomIndex;
            vector<int> validIndexes;
            int freeCoordinates[10][2];    // [index][0-y 1-x]

            for (int y = smallerY-1; y <= biggerY+1; y++)       //get coordinates around two organisms
            {
                if(y != smallerY && y != biggerY && y >= 0 && y < worldSizeY) 
                {
                    for (int x = smallerX-1; x <= biggerX+1; x++)
                    {
                        if (x != smallerX && x != biggerX && x >= 0 && x < worldSizeX)
                        {
                            freeCoordinates[freeSpaces][0] = y;
                            freeCoordinates[freeSpaces][1] = x;
                            validIndexes.push_back(freeSpaces);
                            freeSpaces++;
                        }
                    }
                }
            }

            for (int i = 0; i < organisms.size(); i++)      //remove 
            {
                for (int j = 0; j < freeSpaces; j++)
                {
                    if (organisms[i]->posY == freeCoordinates[j][0] && organisms[i]->posX == freeCoordinates[j][1])
                    {
                        validIndexes.erase(validIndexes.begin() + j);
                        freeSpaces--;
                    }
                }
            }
            validIndexes.shrink_to_fit();

            if (freeSpaces > 1)
            {
                randomIndex = randInt(0, validIndexes.size()-1);
                newY = freeCoordinates[randomIndex][0];
                newX = freeCoordinates[randomIndex][1];
                Transporter *data = new Transporter(id, newX, newY, this->animal);
                cout << "New animal " << name << " has been born" << endl;
                return data;
            }
            else if(freeSpaces == 1)
            {
                newY = freeCoordinates[0][0];
                newX = freeCoordinates[0][1];
                Transporter *data = new Transporter(id, newX, newY, this->animal);
                cout << "New animal " << name << " has been born" << endl;
                return data;
            }
            else return NULL;
        }
        else
        {
            if(randInt(0, 1))
            {
                if (enemy->strength > strength)
                {
                    alive = false;
                    cout << name << " has died to " << enemy->name << endl;
                    return NULL;
                }
                else
                {
                    enemy->alive = false;
                    cout << enemy->name << " has died to " << name << endl;
                    return NULL;
                }
            }
            else
            {
                vector<Coordinates> freeSpaces;
                for (int i = -1; i <= 1; i++)
                {
                    for (int j = -1; j <= 1; j++)
                    {
                        if (i != 0 && j != 0)
                        {
                            int cellx = j+posX, celly = i+posY;
                            for (int k = 0; k < organisms.size(); k++)
                            {
                                if(organisms[k]->posX == cellx && organisms[k]->posY == celly)
                                {
                                    if(organisms[k]->strength <= strength) freeSpaces.push_back(Coordinates(celly, cellx));
                                }
                            }
                        }
                    }
                }

                if (freeSpaces.size() > 0)
                {
                    int randomIndex;
                    if(freeSpaces.size() == 1) randomIndex = 0;
                    else randomIndex = randInt(0, freeSpaces.size()-1);

                    prevX = posX;
                    prevY = posY;
                    posX = freeSpaces[randomIndex].x;
                    posY = freeSpaces[randomIndex].y;
                    cout << name << " has fled from " << enemy->name;
                    return NULL;
                }
                else
                {
                    if (enemy->strength > strength)
                    {
                        alive = false;
                        cout << name << " has died to " << enemy->name << endl;
                        return NULL;
                    }
                    else
                    {
                        enemy->alive = false;
                        cout << enemy->name << " has died to " << name << endl;
                        return NULL;
                    }
                }
            }
        }
    }
};