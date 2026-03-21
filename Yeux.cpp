#include "Yeux.h"
#include <iostream>

Yeux::Yeux(float a, float r, float dCoef){
    angle = a;
    range = r;
    detectCoef = dCoef;
}

Yeux::~Yeux(){
    
}

bool Yeux::detect(const Bestiole & b, double dist, double a) const{
    return (dist <= range && abs(a) <= angle && detectCoef > b.camoCoef);
}