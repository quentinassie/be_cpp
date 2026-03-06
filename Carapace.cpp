#include "Carapace.h"
#include <iostream>

Carapace::Carapace(float rCoef, float sCoef){
    resistCoef = rCoef;
    slowCoef = sCoef;
}

Carapace::~Carapace(){
    
}

void Carapace::update(Bestiole* bestiole){
    probabilité = bestiole->getProbaMortCollision();
    bestiole->setProbaMortCollision(probabilité / resistCoef);
    
    vitesse = bestiole->getVitesse();
    bestiole->setVitesse(vitesse / slowCoef);
}