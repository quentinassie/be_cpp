#ifndef _CAMOUFLAGE_H_
#define _CAMOUFLAGE_H_
#include "UImg.h"
#include <iostream>

#include "Accessoire.h"

class Bestiole;

//Structure Camouflage : contient
//   - un constructeur avec paramètres devant être appelé par la factory lors de la création de la bestiole
//   - un destructeur 
//La classe Bestiole a accés aux attribus pour les méthodes jeTeVois et update

struct Camouflage : public Accessoire 
{
    private :
        float camoCoef;

    public:

        Camouflage(float cCoef);
        Camouflage(const Camouflage& other);
        ~Camouflage();

        float getCamouflage() const;

        std::unique_ptr<Accessoire> clone() const override;

        void update(Bestiole* bestiole) const override;
};

#endif