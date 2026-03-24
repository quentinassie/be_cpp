#include "Carapace.h"
#include <iostream>
#include "Bestiole.h"
#include "Milieu.h"



Carapace::Carapace(float rCoef, float sCoef){
    resistCoef = rCoef;
    slowCoef = sCoef;
}
Carapace::Carapace(const Carapace& other){
    resistCoef = other.resistCoef;
    slowCoef = other.slowCoef;
}

Carapace::~Carapace(){
    
}

std::unique_ptr<Accessoire> Carapace::clone() const
{
    return std::unique_ptr<Accessoire>(new Carapace(*this));
}

void Carapace::update(Bestiole* bestiole) const {
    double proba = bestiole->getProbaCollisionFatale();
    bestiole->setProbaCollisionFatale(proba / resistCoef);
    bestiole->multVitesse(slowCoef);
}