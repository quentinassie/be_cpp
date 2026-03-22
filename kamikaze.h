#ifndef _KAMIKAZE_H_
#define _KAMIKAZE_H_

#include "Comportement.h"
#include "UImg.h"
#include <array>

class Kamikaze : public Comportement {

public:


    void updateDirection(Bestiole& b, Milieu& m) override;

    std::array<T,3> getCouleur() override;
    

};

#endif