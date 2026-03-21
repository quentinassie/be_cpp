#include "Oreilles.h"
#include <iostream>

Oreilles::Oreilles(float r, float cdCoef){
    range = r;
    detectCoef = dCoef;
}

Oreilles::~Oreilles(){

}

bool Oreilles::detect(const Bestiole & b, double dist, double angle) const{
    return (dist <= range && detectCoef > b.camoCoef);
}