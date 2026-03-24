#ifndef _CARAPACE_H_
#define _CARAPACE_H_
#include "UImg.h"
#include <iostream>

#include "Accessoire.h"

class Bestiole;

//Structure Carapace : contient
//   - un constructeur avec paramètres devant être appelé par la factory lors de la création de la bestiole
//   - un destructeur 
//La classe Bestiole a accés aux attribus pour les méthodes jeTeVois et update

struct Carapace : public Accessoire 
{
    private :
        float resistCoef;
        float slowCoef;
        double probaCollFatale;

    public:
        Carapace(float rCoef, float sCoef);
        Carapace(const Carapace& other);
        ~Carapace();

    std::unique_ptr<Accessoire> clone() const override;
    void setProbaCollisionFatale(double proba){probaCollFatale = proba;};
    void update(Bestiole* bestiole) const override;
};

#endif