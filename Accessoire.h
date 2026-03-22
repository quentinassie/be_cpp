#ifndef ACCESSOIRE_H
#define ACCESSOIRE_H

#include <memory>

class Bestiole;

class Accessoire
{
public:
    virtual ~Accessoire() = default;
    virtual std::unique_ptr<Accessoire> clone() const = 0;
    virtual void update(Bestiole* bestiole) const = 0;
};

#endif