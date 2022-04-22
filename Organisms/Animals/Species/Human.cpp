#pragma once
#include "../Animal.cpp"
#include "../../../Global.h"

class Human : public Animal {
    int id = 0;
    int strength = 5;
    int initiative = 4;
};