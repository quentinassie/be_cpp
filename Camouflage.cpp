#include "Camouflage.h"
#include <iostream>

Camouflage::Camouflage(float cCoef){
    camoCoef = cCoef;
}

Camouflage::~Camouflage(){
    
}

std::unique_ptr<Accessoire> Camouflage::clone() const
{
    return std::make_unique<Camouflage>(*this);
}

void Camouflage::update(Bestiole* bestiole){
    bestiole->setCamoCoef(camoCoef);
}