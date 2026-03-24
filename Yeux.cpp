#include "Yeux.h"
#include <iostream>
#include "Bestiole.h"

Yeux::Yeux(float a, float r, float dCoef){
    angle = a;
    range = r;
    detectCoef = dCoef;
}
Yeux::Yeux(const Yeux& y){
    angle = y.angle;
    range = y.range;
    detectCoef = y.detectCoef;
}

Yeux::~Yeux(){
    
}

std::unique_ptr<Capteur> Yeux::clone() const
{
    return std::unique_ptr<Capteur>(new Yeux(*this));
}

bool Yeux::detect(const Bestiole & b, double dist, double a) const {
    return (dist <= range && abs(a) <= angle && detectCoef > b.getCamoCoef())
}