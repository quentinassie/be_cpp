#include "prevoyante.h"
#include "Bestiole.h"
#include "Milieu.h"

#include <cmath>



void Prevoyante::updateDirection(Bestiole& b, Milieu& m)
{
    auto voisins = m.getVoisins(b);
    if (voisins.empty()) return;

    std::shared_ptr<Bestiole> target = voisins[0];
    double minDist = std::hypot(target->getX() - b.getX(), target->getY() - b.getY());

    for (auto& v : voisins) {
        double d = std::hypot(v->getX() - b.getX(), v->getY() - b.getY());
        if (d < minDist) {
            minDist = d;
            target = v;
        }
    }

    const double horizon = 3.0;
    const double seuilDanger = 25.0;

    double bxFuture = b.getX() + std::cos(b.getOrientation()) * b.getVitesse() * horizon;
    double byFuture = b.getY() - std::sin(b.getOrientation()) * b.getVitesse() * horizon;

    double vxFuture = target->getX() + std::cos(target->getOrientation()) * target->getVitesse() * horizon;
    double vyFuture = target->getY() - std::sin(target->getOrientation()) * target->getVitesse() * horizon;

    double dist = std::hypot(bxFuture - vxFuture, byFuture - vyFuture);

    if (dist < seuilDanger) {
        double dx = target->getX() - b.getX();
        double dy = b.getY() - target->getY();

        double angleVersVoisin = std::atan2(dy, dx);
        double ecart = angleVersVoisin - b.getOrientation();

        while (ecart > M_PI) ecart -= 2 * M_PI;
        while (ecart < -M_PI) ecart += 2 * M_PI;

        if (ecart > 0) {
            b.setOrientation(b.getOrientation() - M_PI / 6.0);
        } else {
            b.setOrientation(b.getOrientation() + M_PI / 6.0);
        }

        b.setVitesseMomentanee(1.5, 5);
    }
}


std::array<T,3> Prevoyante :: getCouleur(){
    return {199, 207, 0}; //vert buisson d'été
}
