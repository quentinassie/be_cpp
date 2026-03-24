#ifndef _NAGEOIRES_H_
#define _NAGEOIRES_H_
#include "UImg.h"
#include <iostream>

#include "Accessoire.h"

class Bestiole;

//Structure Nageoires : contient
//   - un constructeur avec paramètres devant être appelé par la factory lors de la création de la bestiole
//   - un destructeur 
//La classe Bestiole a accés aux attribus pour les méthodes jeTeVois et update

struct Nageoires : public Accessoire 
{
    private:
        double speedCoef;

    public:

        Nageoires(double sCoef);
        Nageoires(const Nageoires& other);
        ~Nageoires();

        std::unique_ptr<Accessoire> clone() const override;
        void update(Bestiole* bestiole) const override;

        void setSpeedCoef(double newcoef){speedCoef = newcoef;};
    };

#endif