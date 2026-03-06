#ifndef _NAGEOIRES_H_
#define _NAGEOIRES_H_
#include "UImg.h"
#include <iostream>

//Structure Nageoires : contient
//   - un constructeur avec paramètres devant être appelé par la factory lors de la création de la bestiole
//   - un destructeur 
//La classe Bestiole a accés aux attribus pour les méthodes jeTeVois et update

struct Nageoires
{
    const float speedCoef;

    Nageoires(float s);
    ~Nageoires();  
}