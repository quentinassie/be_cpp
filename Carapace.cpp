#include "Carapace.h"
#include <iostream>
#include "Bestiole.h"

Carapace::Carapace(float rCoef, float sCoef){
    resistCoef = rCoef;
    slowCoef = sCoef;
}

Carapace::~Carapace(){
    
}

std::unique_ptr<Accessoire> Carapace::clone() const
{
    return std::unique_ptr<Accessoire>(new Carapace(*this));
}

void Carapace::update(Bestiole* bestiole) const {
    //probabilite = bestiole->getProbaMortCollision();
    //bestiole->setProbaMortCollision(probabilite / resistCoef);
    
    //vitesse = bestiole->getVitesse();
    //bestiole->setVitesse(vitesse / slowCoef);
}