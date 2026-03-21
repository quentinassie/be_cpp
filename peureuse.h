#ifndef _PEUREUSE_H_
#define _PEUREUSE_H_

#include "Comportement.h"
#include "UImg.h"
#include <array>

class Peureuse : public Comportement {

public:


    void updateDirection(Bestiole& b, Milieu& m) override;

    std::array<T,3> getCouleur() override;
    

};

#endif