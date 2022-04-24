#pragma once
#include "../Organism.cpp"

class Animal : public Organism {
public:
    Animal() : Organism()
    {
        animal = true;
    }
};