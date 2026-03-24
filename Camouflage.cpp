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
    return std::unique_ptr<Accessoire>(new Camouflage(*this));
}

void Camouflage::update(Bestiole* bestiole) const
{
    // no-op pour l'instant
    //bestiole->setCamoCoef(camoCoef);
    (void)bestiole;
}