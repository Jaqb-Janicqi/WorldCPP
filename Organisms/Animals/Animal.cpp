#pragma once
#include "../Organism.cpp"
#include "../../Global.h"

class Animal : public Organism {
public:
    Animal(){
        animal = true;
    }
};