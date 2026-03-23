#ifndef _OREILLES_H_
#define _OREILLES_H_
#include "UImg.h"
#include <iostream>

#include "Capteur.h"

class Bestiole;

//Structure Oreilles : contient
//   - un constructeur avec paramètres devant être appelé par la factory lors de la création de la bestiole
//   - un destructeur 
//La classe Bestiole a accés aux attribus pour les méthodes jeTeVois et update

struct Oreilles : public Capteur
{
    private :
        float range;
        float detectCoef;

    public :
        Oreilles(float r, float dCoef);
        Oreilles(const Oreilles& o);
        ~Oreilles();

        std::unique_ptr<Capteur> clone() const override;
        bool detect(const Bestiole & b, double dist, double angle) const override;
};

#endif