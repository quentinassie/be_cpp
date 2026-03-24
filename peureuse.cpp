#include "peureuse.h"
#include "Bestiole.h"
#include "Milieu.h"

#include <cmath>


void Peureuse::updateDirection(Bestiole& b, Milieu& m)
{
    auto voisins = m.getVoisins(b);

    double sumX = 0.0;
    double sumY = 0.0;
    int nbProches = 0;

    for (const auto& v : voisins) {
        double dx = v->getX() - b.getX();
        double dy = b.getY() - v->getY();
        double dist = std::sqrt(dx * dx + dy * dy);

        if (dist <= 2000.0) {
            sumX += dx;
            sumY += dy;
            nbProches++;
        }
    }

    if (nbProches >= 1) {
        double meanAngle = std::atan2(sumY, sumX);
        b.setOrientation(meanAngle + 3.141592653589793);
        b.setVitesseMomentanee(2.0, 8);
    }
}
std::array<T,3> Peureuse :: getCouleur(){
    return {116, 208, 241};
}
