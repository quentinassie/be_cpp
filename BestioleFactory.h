#ifndef _BESTIOLE_FACTORY_
#define _BESTIOLE_FACTORY_

#include "Bestiole.h"
#include <map>
#include <memory>
#include <iostream>
#include <string>

struct BestioleFactory {
    // Dictionnaire de comportements disponibles
    std::map<std::string, std::shared_ptr<Comportement>> comportement_dict;

    // Distribution des comportements
    std::map<std::string, double> distributionComportements;

    // Paramètres généraux
    int nombrePopulationInitiale;
    double tauxNaissanceGlobal;
    double probaClonage;

    // Plage d'angle de vision
    double angleVisionMin, angleVisionMax;

    // Plage de distance de vision
    double distVisionMin, distVisionMax;

    // Plage de capacité de détection par les yeux
    double detectVisionMin, detectVisionMax;

    // Plage de capacité de détection par les oreilles
    double detectAuditionMin, detectAuditionMax;

    // Plage de distance d'audition
    double distAuditionMin, distAuditionMax;

    // Plage de camouflage (0.0 = invisible, 1.0 = opaque)
    double camouflageMin, camouflageMax;

    // Réduction de vitesse maximal pour la carapace et Resistance
    double carapaceSlowMax, carapaceResistCoefMax;

    // Augmentation de vitesse maximal pour les nageoires
    double nageoiresSpeedCoefMax;

    int ageMax;
    int ageMin;
    
    double probaCollisionFatale;
    double tailleMax;

    BestioleFactory(const std::string& configFile);
    ~BestioleFactory();

    void chargerConfiguration(const std::string& configFile);
    std::shared_ptr<Bestiole> createBestiole(std::string comportement);
    std::shared_ptr<Bestiole> createBestioleAleatoire();

    bool find(std::unique_ptr<Capteur>& capteur, std::vector<std::unique_ptr<Capteur>>& capteurs);
    std::unique_ptr<Capteur> choisirCapteur();

    bool find(std::unique_ptr<Accessoire>& accessoire, const std::vector<std::unique_ptr<Accessoire>>& accessoires);
    std::unique_ptr<Accessoire> choisirAccessoire();

    int randomInt(int min, int max);
    double randomDouble(double min, double max);

    std::shared_ptr<Comportement> getComportementAleatoire();
};

#endif