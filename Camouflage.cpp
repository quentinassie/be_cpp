#include "Camouflage.h"
#include "Bestiole.h" 

Camouflage::Camouflage(float cCoef)
{
    camoCoef = cCoef;
}

Camouflage::Camouflage(const Camouflage& other){
    camoCoef = other.camoCoef;
}
Camouflage::~Camouflage()
{
}

float Camouflage::getCamouflage() const
{
    return camoCoef;
}

std::unique_ptr<Accessoire> Camouflage::clone() const
{
    return std::make_unique<Camouflage>(*this);
}

void Camouflage::update(Bestiole* bestiole) const
{
    // no-op pour l'instant
    //bestiole->setCamoCoef(camoCoef);
    (void)bestiole;
}