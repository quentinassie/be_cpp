#ifndef _CARAPACE_H_
#define _CARAPACE_H_
#include "UImg.h"
#include <iostream>

//Structure Carapace : contient
//   - un constructeur avec paramètres devant être appelé par la factory lors de la création de la bestiole
//   - un destructeur 
//La classe Bestiole a accés aux attribus pour les méthodes jeTeVois et update

struct Carapace
{
    const float resistCoef;
    const float slowCoef;

    Carapace(float r, float s);
    ~Carapace();  
}