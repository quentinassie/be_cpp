#include "BestioleFactory.h"
#include <iostream>
#include <random>
#include <string>
#include <stdexcept>

#include "SimpleIni.h"
#include "Bestiole.h"
#include "gregaire.h"
#include "peureuse.h"
#include "kamikaze.h"
#include "prevoyante.h"
#include "PersonnaliteMultiple.h"

#include "Camouflage.h"
#include "Carapace.h"
#include "Nageoires.h"
#include "Yeux.h"
#include "Oreilles.h"


BestioleFactory::BestioleFactory(const std::string& configFile) {
    std::cout << "BestioleFactory created" << std::endl;
    chargerConfiguration(configFile);

    comportement_dict = {
        {"gregaire", std::make_shared<Gregaire>()},
        {"peureuse", std::make_shared<Peureuse>()},
        {"kamikaze", std::make_shared<Kamikaze>()},
        {"prevoyante", std::make_shared<Prevoyante>()},
        {"personnalitemultiple", std::make_shared<PersonnaliteMultiple>()}

    };
}

BestioleFactory::~BestioleFactory() {
    std::cout << "BestioleFactory destroyed" << std::endl;
}

void BestioleFactory::chargerConfiguration(const std::string& configFile) {
    CSimpleIniA ini;
    ini.SetUnicode();

    SI_Error rc = ini.LoadFile(configFile.c_str());
    if (rc < 0) {
        throw std::runtime_error("Impossible d'ouvrir le fichier de configuration: " + configFile);
    }

    // Charger les distributions de comportements
    distributionComportements["gregaire"] =
        std::stof(ini.GetValue("population.comportements", "gregaire", "0.1"));

    distributionComportements["peureuse"] =
        std::stof(ini.GetValue("population.comportements", "peureuse", "0.1"));
    
    distributionComportements["kamikaze"] =
        std::stof(ini.GetValue("population.comportements", "kamikaze", "0.1"));

    distributionComportements["prevoyante"] =
        std::stof(ini.GetValue("population.comportements", "prevoyante", "0.1"));

    distributionComportements["personnalitemultiple"] =
        std::stof(ini.GetValue("population.comportements", "personnalitemultiple", "0.1"));

    // Charger le nombre de population initiale
    nombrePopulationInitiale =
        std::stoi(ini.GetValue("population", "nombre", "5"));

    // Charger les paramètres généraux
    tauxNaissanceGlobal =
        std::stof(ini.GetValue("general", "naissance", "0.1"));
    ageMax =
        std::stoi(ini.GetValue("general", "age_max", "80"));
    probaClonage =
        std::stof(ini.GetValue("general", "clonage", "0.1"));
    tailleMax = 
        std::stof(ini.GetValue("general", "taille_max", "2.0"));
    // Charger les plages de caractéristiques
    angleVisionMin =
        std::stof(ini.GetValue("angle_vision", "min", "20.0"));
    angleVisionMax =
        std::stof(ini.GetValue("angle_vision", "max", "120.0"));

    distVisionMin =
        std::stof(ini.GetValue("distance_vision", "min", "5.0"));
    distVisionMax =
        std::stof(ini.GetValue("distance_vision", "max", "80.0"));

    distAuditionMin =
        std::stof(ini.GetValue("distance_audition", "min", "30.0"));
    distAuditionMax =
        std::stof(ini.GetValue("distance_audition", "max", "100.0"));

    camouflageMin =
        std::stof(ini.GetValue("camouflage", "min", "0.3"));
    camouflageMax =
        std::stof(ini.GetValue("camouflage", "max", "1.0"));

    carapaceSlowMax =
        std::stof(ini.GetValue("carapace", "slow", "0.3"));
    carapaceResistCoefMax =
        std::stof(ini.GetValue("carapace", "slow", "3.0"));

    nageoiresSpeedCoefMax =
        std::stof(ini.GetValue("nageoires", "max", "2.0"));

    detectVisionMin =
        std::stof(ini.GetValue("detect_vision", "min", "0"));
    detectVisionMax =
        std::stof(ini.GetValue("detect_vision", "max", "1.0"));

    detectAuditionMin =
        std::stof(ini.GetValue("detect_audition", "min", "0"));
    detectAuditionMax =
        std::stof(ini.GetValue("detect_audition", "max", "1.0"));

    probaCollisionFatale =
        std::stof(ini.GetValue("collision", "defaut", "0.3"));

    std::cout << "Configuration chargée depuis " << configFile << std::endl;
}

std::shared_ptr<Bestiole> BestioleFactory::createBestiole(std::string comportement) {
    auto bestiole = std::make_shared<Bestiole>();

    // choisir des accessoires aléatoires
    int numAccessoires = randomInt(0, 3); // 0, 1, 2 ou 3 accessoires
    for (int i = 0; i < numAccessoires; ++i) {
            std::unique_ptr<Accessoire> accessoire = choisirAccessoire();
            if (accessoire && !find(accessoire, bestiole->getAccessoires())) {
                bestiole->getAccessoires().push_back(std::move(accessoire));
            }
    }

    // choisir des capteurs aléatoires
    int numCapteurs = randomInt(0, 2); // 0, 1 ou 2 capteurs
    for (int i = 0; i < numCapteurs; ++i) {
        std::unique_ptr<Capteur> capteur = choisirCapteur();
        if (capteur && !find(capteur, bestiole->getCapteurs())) {
            bestiole->getCapteurs().push_back(std::move(capteur));
        }
    }

    // Assigner le comportement
    if (comportement_dict.find(comportement) != comportement_dict.end()) {
        bestiole->setComportement(comportement_dict[comportement]);
    }

    // ralentir la kamikaze
    if (comportement == "kamikaze") {
        bestiole->setVitesse(3);
    }   


    bestiole->setProbaCollisionFatale(probaCollisionFatale);

    bestiole->setAgeMax(ageMax);   

    //taille aléatoire
    double rdtaille = randomDouble(1.0, tailleMax);
    bestiole->setTaille(rdtaille);

    bestiole->activateAccessoires(); //activer les effets de chacun des accessoires ajoutés dans la bestiole

     

    return bestiole;
}

bool BestioleFactory::find(std::unique_ptr<Accessoire>& accessoire, const std::vector<std::unique_ptr<Accessoire>>& accessoires){
    for (const auto& acc : accessoires) {
        if (typeid(*acc) == typeid(*accessoire)) {
            return true; // Accessoire du même type trouvé
        }
    }
    return false; // Aucun accessoire du même type trouvé
}

bool BestioleFactory::find(std::unique_ptr<Capteur>& capteur, std::vector<std::unique_ptr<Capteur>>& capteurs){
    for (const auto& c : capteurs) {
        if (typeid(*c) == typeid(*capteur)) {
            return true; // Capteur du même type trouvé
        }
    }
    return false; // Aucun capteur du même type trouvé
}

std::unique_ptr<Accessoire> BestioleFactory::choisirAccessoire(){
    int randomIndex = randomInt(0,3); // 0: Camouflage, 1: Carapace, 2: Nageoire, 3: Aucun
    if (randomIndex == 0) {
        double camoufl = randomDouble(camouflageMin, camouflageMax);
        auto camouflage = std::unique_ptr<Camouflage>(new Camouflage(camoufl));
        return camouflage;
    }
    else if (randomIndex == 1) {
        double slow = randomDouble(carapaceSlowMax,1);
        double resist = randomDouble(1, carapaceResistCoefMax);
        auto carapace = std::unique_ptr<Carapace>(new Carapace(resist,slow));
        carapace->setProbaCollisionFatale(probaCollisionFatale);
        return carapace;
    }
    else if (randomIndex == 2) {
        double speed = randomDouble(1, nageoiresSpeedCoefMax);
        auto nageoires = std::unique_ptr<Nageoires>(new Nageoires(speed));
        return nageoires;
    }
    else {
        return nullptr; // Aucun accessoire
    }
}

std::unique_ptr<Capteur> BestioleFactory::choisirCapteur(){
    int randomIndex = randomInt(0,2); // 0: Yeux, 1: Oreilles, 2: Aucun

    if (randomIndex == 0) {
        double angle = randomDouble(angleVisionMin, angleVisionMax);
        double vision = randomDouble(distVisionMin, distVisionMax);
        double detection = randomDouble(detectVisionMin, detectVisionMax);
        auto yeux = std::unique_ptr<Yeux>(new Yeux(angle, vision, detection));
        return yeux;
    }
    else if (randomIndex == 1) {
        double audition = randomDouble(distAuditionMin, distAuditionMax);
        double detect = randomDouble(detectAuditionMin, detectAuditionMax);
        auto oreilles = std::unique_ptr<Oreilles>(new Oreilles(audition, detect));
        return oreilles;
    }
    else {
        return nullptr; // Aucun capteur
    }
}

int BestioleFactory::randomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

double BestioleFactory::randomDouble(double min, double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(min, max);
    return dist(gen);
}

std::shared_ptr<Bestiole> BestioleFactory::createBestioleAleatoire() {
    double total = 0.0;

    for (auto elem : distributionComportements) {
        total += elem.second;
    }

    double tirage = randomDouble(0.0, total);
    double somme = 0.0;
    
    for (auto elem : distributionComportements) {
        somme += elem.second;

        if (tirage <= somme) {
            return createBestiole(elem.first);
        }
    }

    return createBestiole("gregaire");
}

//pour le changement en cas d'evenement exterieur (touche c)
std::shared_ptr<Comportement> BestioleFactory::getComportementAleatoire()
{
    int com = randomInt(0, 4);

    switch (com) {
        case 0: return comportement_dict["gregaire"];
        case 1: return comportement_dict["peureuse"];
        case 2: return comportement_dict["kamikaze"];
        case 3: return comportement_dict["prevoyante"];
        default: return comportement_dict["personnalitemultiple"];
    }
}