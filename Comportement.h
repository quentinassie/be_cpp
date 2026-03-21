#ifndef _COMPORTEMENT_H_
#define _COMPORTEMENT_H_
#include <iostream>
#include "UImg.h"
#include <array>

class Bestiole;
class Milieu;

// Strategie pattern
class Comportement {

public:
    
    virtual ~Comportement() {}

    // à chaque step
    virtual void updateDirection(Bestiole& b, Milieu& m) = 0;

    virtual std::array<T,3> getCouleur() = 0;


};

#endif