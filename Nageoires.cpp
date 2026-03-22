#include "Nageoires.h"
#include <iostream>

Nageoires::Nageoires(float sCoef){
    speedCoef = sCoef;
}

Nageoires::~Nageoires(){
    
}

std::unique_ptr<Accessoire> Nageoires::clone() const
{
    return std::make_unique<Nageoires>(*this);
}

void Nageoires::update(Bestiole* bestiole){
    vitesse = bestiole->getVitesse();
    bestiole->setVitesse(vitesse * speedCoef);
}