#include "PersonnaliteMultiple.h"
#include "gregaire.h"
#include "peureuse.h"
#include "kamikaze.h"
#include "prevoyante.h"
#include <cstdlib>
#include <memory>

PersonnaliteMultiple::PersonnaliteMultiple() {
    comportements.push_back(std::make_shared<Gregaire>());
    comportements.push_back(std::make_shared<Peureuse>());
    comportements.push_back(std::make_shared<Kamikaze>());
    comportements.push_back(std::make_shared<Prevoyante>());

    courant = comportements[rand() % comportements.size()];
}

void PersonnaliteMultiple::updateDirection(Bestiole& b, Milieu& m) {
    // 3% de chance de changer de personnalité à chaque tour
    if ((static_cast<double>(rand()) / RAND_MAX) < 0.03) {
        courant = comportements[rand() % comportements.size()];
    }

    courant->updateDirection(b, m);
}

std::array<T,3> PersonnaliteMultiple::getCouleur() {
    if (courant) return courant->getCouleur();
    return {0, 0, 0};
}