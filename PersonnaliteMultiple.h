#ifndef _PERSONNALITEMULTIPLE_H_
#define _PERSONNALITEMULTIPLE_H_

#include "Comportement.h"
#include "UImg.h"
#include <array>
#include <iostream>
#include <vector>
#include <memory>




class PersonnaliteMultiple : public Comportement {
private:
    std::vector<std::shared_ptr<Comportement>> comportements;
    std::shared_ptr<Comportement> courant;

public:
    PersonnaliteMultiple();
    void updateDirection(Bestiole& b, Milieu& m) override;
    std::array<T,3> getCouleur() override;
};


#endif