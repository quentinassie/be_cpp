#ifndef _OREILLES_H_
#define _OREILLES_H_
#include "UImg.h"
#include <iostream>

#include "Capteur.h"

//Structure Oreilles : contient
//   - un constructeur avec paramètres devant être appelé par la factory lors de la création de la bestiole
//   - un destructeur 
//La classe Bestiole a accés aux attribus pour les méthodes jeTeVois et update

struct Oreilles : public Capteur
{
    const float range;
    const float detectCoef;

    Oreilles(float r, float dCoef);
    ~Oreilles();

    std::unique_ptr<Capteur> clone() const override;
    bool detect(const Bestiole & b, double dist, double angle) const;
};

#endif