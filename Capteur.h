#ifndef CAPTEUR_H
#define CAPTEUR_H

#include <memory>

class Capteur
{
public:
    virtual ~Capteur() = default;
    virtual std::unique_ptr<Capteur> clone() const = 0;
};

#endif