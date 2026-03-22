#ifndef _PREVOYANTE_H_
#define _PREVOYANTE_H_

#include "Comportement.h"
#include "UImg.h"
#include <array>

class Prevoyante : public Comportement {

public:


    void updateDirection(Bestiole& b, Milieu& m) override;

    std::array<T,3> getCouleur() override;
    

};

#endif