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

BestioleFactory::BestioleFactory(const std::string& configFile) {
    std::cout << "BestioleFactory created" << std::endl;
    chargerConfiguration(configFile);

    comportement_dict = {
        {"gregaire", std::make_shared<Gregaire>()},
        {"peureuse", std::make_shared<Peureuse>()},
        {"kamikaze", std::make_shared<Kamikaze>()},
        {"prevoyante", std::make_shared<Prevoyante>()}

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

    // Assigner le comportement
    if (comportement_dict.find(comportement) != comportement_dict.end()) {
        bestiole->setComportement(comportement_dict[comportement]);
    }

    bestiole->setProbaCollisionFatale(probaCollisionFatale);
    bestiole->setAgeMax(ageMax);    

    return bestiole;
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