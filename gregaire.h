#ifndef _GREGAIRE_H_
#define _GREGAIRE_H_

#include "Comportement.h"
#include "UImg.h"
#include <array>

class Gregaire : public Comportement {

public:


    void updateDirection(Bestiole& b, Milieu& m) override;

    std::array<T,3> getCouleur() override;
    

};

#endif