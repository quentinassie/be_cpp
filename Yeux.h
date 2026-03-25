#ifndef _YEUX_H_
#define _YEUX_H_
#include "UImg.h"
#include <iostream>

#include "Capteur.h"

class Bestiole;
//Structure Yeux : contient
//   - un constructeur avec paramètres devant être appelé par la factory lors de la création de la bestiole
//   - un destructeur 
//La classe Bestiole a accés aux attribus pour les méthodes jeTeVois et update

struct Yeux : public Capteur
{
    private:
        float angle;
        float range;
        float detectCoef;
    public :
        Yeux(float a, float r, float dCoef);
        Yeux(const Yeux& y);
        ~Yeux();  

        float getAngle() const { return angle; }
        float getRange() const { return range; }

        std::unique_ptr<Capteur> clone() const override;
        bool detect(const Bestiole & b, double dist, double a) const override;
};

#endif