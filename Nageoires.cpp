#include "Nageoires.h"
#include <iostream>

Nageoires::Nageoires(float sCoef){
    speedCoef = sCoef;
}

Nageoires::~Nageoires(){
    
}

void Nageoires::update(Bestiole* bestiole){
    vitesse = bestiole->getVitesse();
    bestiole->setVitesse(vitesse * speedCoef);
}