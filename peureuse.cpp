#include "peureuse.h"
#include "Bestiole.h"
#include "Milieu.h"

#include <cmath>


void Peureuse::updateDirection(Bestiole& b, Milieu& m)
{
    
    auto voisins = m.getVoisins(b);

    if (voisins.size() > 0) { //1 bestioles autour et c'est la fuite
        double sumX = 0.0;
        double sumY = 0.0;

        for (auto v : voisins) {
            sumX += v->getX() - b.getX();
            sumY += b.getY() - v->getY();
        }

        double meanAngle = std::atan2(sumY, sumX);

        b.setOrientation(meanAngle + 3.141592653589793);
        b.setVitesseMomentanee(2.0, 8);
    }
}

std::array<T,3> Peureuse :: getCouleur(){
    return {116, 208, 241};
}
