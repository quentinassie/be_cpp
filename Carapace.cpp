#include "Carapace.h"
#include <iostream>

Carapace::Carapace(float rCoef, float sCoef){
    resistCoef = rCoef;
    slowCoef = sCoef;
}

Carapace::~Carapace(){
    
}

std::unique_ptr<Accessoire> Carapace::clone() const
{
    return std::make_unique<Carapace>(*this);
}

void Carapace::update(Bestiole* bestiole){
    probabilité = bestiole->getProbaMortCollision();
    bestiole->setProbaMortCollision(probabilité / resistCoef);
    
    vitesse = bestiole->getVitesse();
    bestiole->setVitesse(vitesse / slowCoef);
}