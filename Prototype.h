#ifndef _Prototype_H_
#define _Prototype_H_

class Prototype
{
    public : 
    virtual Prototype* clone() const = 0;
    virtual ~Prototype() = default;
};

#endif