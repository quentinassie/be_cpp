#include "Camouflage.h"
#include <iostream>

Camouflage::Camouflage(float cCoef){
    camoCoef = cCoef;
}

Camouflage::~Camouflage(){
    
}

void Camouflage::update(Bestiole* bestiole){
    bestiole->setCamoCoef(camoCoef);
}