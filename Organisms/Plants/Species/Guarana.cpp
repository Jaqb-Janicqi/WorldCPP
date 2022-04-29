#pragma once
#include "../Plant.cpp"


class Guarana : public Plant {
public:
    Guarana(int x, int y) : Plant()
    {
        posX = x;
        posY = y;
        prevX = posX;
        prevY = posY;
        id = 3;
        baseStrength = strength = 0;
        skin = 'G';
        name = "Guarana";
    }

    Guarana()
    {
        posX = randInt(0, worldSizeX);
        posY = randInt(0, worldSizeY);
        Guarana(posX, posY);
    }

    virtual Transporter* collision(Organism *enemy, vector<Organism*> &organisms, vector<string> &events)
    {
        enemy->strength += 3;
        enemy->baseStrength += 3;
        alive = false;
        events.push_back(name + " has been eaten by " + enemy->name + ".");
        return NULL;
    }
};