#ifndef _YEUX_H_
#define _YEUX_H_
#include "UImg.h"
#include <iostream>

//Structure Yeux : contient
//   - un constructeur avec paramètres devant être appelé par la factory lors de la création de la bestiole
//   - un destructeur 
//La classe Bestiole a accés aux attribus pour les méthodes jeTeVois et update

struct Yeux
{
    const float angle;
    const float range;
    const float detectCoef;

    Yeux(float a, float r, float dCoef);
    ~Yeux();  
};

#endif