#ifndef _CAMOUFLAGE_H_
#define _CAMOUFLAGE_H_
#include "UImg.h"
#include <iostream>

//Structure Camouflage : contient
//   - un constructeur avec paramètres devant être appelé par la factory lors de la création de la bestiole
//   - un destructeur 
//La classe Bestiole a accés aux attribus pour les méthodes jeTeVois et update

struct Camouflage
{
    const float camoCoef;

    Camouflage(float c);
    ~Camouflage();  
}