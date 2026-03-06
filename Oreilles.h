#ifndef _OREILLES_H_
#define _OREILLES_H_
#include "UImg.h"
#include <iostream>

//Structure Oreilles : contient
//   - un constructeur avec paramètres devant être appelé par la factory lors de la création de la bestiole
//   - un destructeur 
//La classe Bestiole a accés aux attribus pour les méthodes jeTeVois et update

struct Oreilles
{
    const float range;
    const float detectCoef;

    Oreilles(float r, float c);
    ~Oreilles();  
}