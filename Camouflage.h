#ifndef _CAMOUFLAGE_H_
#define _CAMOUFLAGE_H_
#include "UImg.h"
#include <iostream>

#include "Accessoire.h"

//Structure Camouflage : contient
//   - un constructeur avec paramètres devant être appelé par la factory lors de la création de la bestiole
//   - un destructeur 
//La classe Bestiole a accés aux attribus pour les méthodes jeTeVois et update

struct Camouflage : public Accessoire 
{
    const float camoCoef;

    Camouflage(float cCoef);
    ~Camouflage();

    std::unique_ptr<Accessoire> clone() const override;
    update(Bestiole* bestiole);
};

#endif