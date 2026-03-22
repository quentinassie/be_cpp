#ifndef ACCESSOIRE_H
#define ACCESSOIRE_H

#include <memory>

class Accessoire
{
public:
    virtual ~Accessoire() = default;
    virtual std::unique_ptr<Accessoire> clone() const = 0;
};

#endif