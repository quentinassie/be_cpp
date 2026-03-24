#include "gregaire.h"
#include "Bestiole.h"
#include "Milieu.h"

#include <cmath>


void Gregaire::updateDirection(Bestiole& b, Milieu& m)
{
    auto voisins = m.getVoisins(b);

    double sumX = 0.0;
    double sumY = 0.0;
    int nbProches = 0;

    for (const auto& v : voisins) {
        double dx = v->getX() - b.getX();
        double dy = v->getY() - b.getY();
        double dist = std::sqrt(dx * dx + dy * dy);

        if (dist <= b.getLimiteVue()) {
            sumX += std::cos(v->getOrientation());
            sumY += std::sin(v->getOrientation());
            nbProches++;
        }
    }

    if (nbProches > 0) {
        double meanAngle = std::atan2(sumY, sumX);
        b.setOrientation(meanAngle);
    }
}

std::array<T,3> Gregaire :: getCouleur(){
    //return {249, 66, 158}; rose plus vif
    return {254, 191, 210};

    
}
