#include "Nageoires.h"
#include "Bestiole.h"
#include <iostream>

Nageoires::Nageoires(float sCoef){
    speedCoef = sCoef;
}
Nageoires::Nageoires(const Nageoires& other){
    speedCoef = other.speedCoef;
}

Nageoires::~Nageoires(){
    
}

std::unique_ptr<Accessoire> Nageoires::clone() const
{
    return std::make_unique<Nageoires>(*this);;
}

void Nageoires::update(Bestiole* bestiole) const {
    //vitesse = bestiole->getVitesse();
    //bestiole->setVitesse(vitesse * speedCoef);
}