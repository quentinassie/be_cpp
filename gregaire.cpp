#include "gregaire.h"
#include "Bestiole.h"
#include "Milieu.h"

#include <cmath>


void Gregaire::updateDirection(Bestiole& b, Milieu& m)
{
    
    auto voisins = m.getVoisins(b);

    if (!voisins.empty()) {
        double sumX = 0.0;
        double sumY = 0.0;

        for (auto v : voisins) {
            sumX += std::cos(v->getOrientation());
            sumY += std::sin(v->getOrientation());
        }

        double meanAngle = std::atan2(sumY, sumX);
        b.setOrientation(meanAngle);
    }
}

std::array<T,3> Gregaire :: getCouleur(){
    //return {249, 66, 158}; rose plus vif
    return {254, 191, 210};

    
}
