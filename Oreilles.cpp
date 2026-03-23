#include "Oreilles.h"
#include "Bestiole.h"
#include <iostream>

Oreilles::Oreilles(float r, float cdCoef){
    range = r;
    detectCoef = cdCoef;
}

Oreilles::Oreilles(const Oreilles& o){
    range = o.range;
    detectCoef = o.detectCoef;
}

Oreilles::~Oreilles(){

}

std::unique_ptr<Capteur> Oreilles::clone() const
{
    return std::make_unique<Oreilles>(*this);
}

bool Oreilles::detect(const Bestiole & b, double dist, double angle) const {
    //return (dist <= range && detectCoef > b.camoCoef);
    return false;
}