#ifndef CAPTEUR_H
#define CAPTEUR_H

#include <memory>

class Bestiole;

class Capteur
{
public:
    virtual ~Capteur() = default;
    virtual std::unique_ptr<Capteur> clone() const = 0;
    virtual bool detect(const Bestiole & b, double dist, double a) const = 0;
};

#endif