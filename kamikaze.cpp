#include "kamikaze.h"
#include "Bestiole.h"
#include "Milieu.h"

#include <cmath>


void Kamikaze::updateDirection(Bestiole& b, Milieu& m)
{
    
    auto target = m.getNearestNeighbour(b);
    if (!target) return;

    double X = target->getX() - b.getX();
    double Y = b.getY() - target->getY();   // y inversé
    double Angle = std::atan2(Y, X);
    b.setOrientation(Angle);
    
}


std::array<T,3> Kamikaze :: getCouleur(){
    return {198, 8, 0}; //rouge agresseur
}
