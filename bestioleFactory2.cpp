#include "BestioleFactory.h"
#include <iostream>
#include <random>
#include <string>
#include "SimpleIni.h"

BestioleFactory::BestioleFactory(const std::string& configFile){
    std::cout<< "BestioleFactory created" << std::endl;
    chargerConfiguration(configFile);
    comportement_dict={
        {"gregaire", std::shared_ptr<Comportement>(new Gregaire())},
        {"peureuse", std::shared_ptr<Comportement>(new Peureuse())},
        {"kamikaze", std::shared_ptr<Comportement>(new Kamikaze())},
        {"prevoyante", std::shared_ptr<Comportement>(new Prevoyante())},
    }
}

BestioleFactory::~BestioleFactory(){
    std::cout<< "BestioleFactory destroyed" << std::endl;
}

void GestionNaissances::chargerConfiguration(const std::string& configFile) {
    CSimpleIniA ini;
    ini.SetUnicode();
    
    SI_Error rc = ini.LoadFile(configFile.c_str());
    if (rc < 0) {
        throw std::runtime_error("Impossible d'ouvrir le fichier de configuration: " + configFile);
    }
    
    // Charger les distributions de comportements
    distributionComportements["gregaire"] = std::stof(ini.GetValue("population.comportements", "gregaire", "0.2"));
    distributionComportements["peureuse"] = std::stof(ini.GetValue("population.comportements", "peureuse", "0.5"));
    distributionComportements["prevoyante"] = std::stof(ini.GetValue("population.comportements", "prevoyante", "0.15"));
    distributionComportements["kamikaze"] = std::stof(ini.GetValue("population.comportements", "kamikaze", "0.0"));
    distributionComportements["personnalite_multiple"] = std::stof(ini.GetValue("population.comportements", "personnalite_multiple", "0.15"));

    // Charger le nombre de population initiale
    nombrePopulationInitiale = std::stoi(ini.GetValue("population", "nombre", "20"));

    // Charger les paramètres généraux
    tauxNaissanceGlobal = std::stof(ini.GetValue("general", "naissance", "0.8"));
    ageMax = std::stoi(ini.GetValue("general", "age_max", "80"));
    probaClonage = std::stof(ini.GetValue("general", "clonage", "0.1"));

    // Charger les plages de caractéristiques

    angleVisionMin = std::stof(ini.GetValue("angle_vision", "min", "20.0"));
    angleVisionMax = std::stof(ini.GetValue("angle_vision", "max", "120.0"));
    
    distVisionMin = std::stof(ini.GetValue("distance_vision", "min", "5.0"));
    distVisionMax = std::stof(ini.GetValue("distance_vision", "max", "80.0"));
    
    distAuditionMin = std::stof(ini.GetValue("distance_audition", "min", "30.0"));
    distAuditionMax = std::stof(ini.GetValue("distance_audition", "max", "100.0"));
    
    camouflageMin = std::stof(ini.GetValue("camouflage", "min", "0.3"));
    camouflageMax = std::stof(ini.GetValue("camouflage", "max", "1.0"));

    detectVisionMin = std::stof(ini.GetValue("detect_vision", "min", "0"));
    detectVisionMax = std::stof(ini.GetValue("detect_vision", "max", "1.0"));

    detectAuditionMin = std::stof(ini.GetValue("detect_audition", "min", "0"));
    detectAuditionMax = std::stof(ini.GetValue("detect_audition", "max", "1.0"));

    probaCollisionFatale = std::stof(ini.GetValue("collision", "defaut", "0.3"));
    
    std::cout << "Configuration chargée depuis " << configFile << std::endl;
}

std::shared_ptr<Bestiole> BestioleFactory::createBestiole(std::string comportement){
    std::shared_ptr<Bestiole> bestiole = new Bestiole();
    // choisir un accessoire aléatoire
    std::unique_ptr<Accessoire> accessoire = choisirAccessoire();
    if (accessoire) {
        bestiole->Accessoires.pushback(std::move(accessoire));
    }
    // choisir un capteur aléatoire
    std::unique_ptr<Capteur> capteur = choisirCapteur();
    if (capteur) {
        bestiole->Capteurs.pushback(std::move(capteur));
    }
    // assigner le comportement
    if (comportement_dict.find(comportement) != comportement_dict.end()) {
        bestiole->comportement = comportement_dict[comportement];
    }
}
std::unique_ptr<Accessoire> BestioleFactory::choisirAccessoire(){
    int randomIndex = randomInt(0,3); // 0: Camouflage, 1: Carapace, 2: Nageoire, 3: Aucun
    if (randomIndex == 0) {
        double camoufl = randomDouble(camouflageMin, camouflageMax);
        return std::make_unique<Camouflage>(camoufl);
    }
    else if (randomIndex == 1) {
        double slow = randomDouble(1, slowCoeffMax);
        double resist = randomDouble(1, resistCoefMax);
        return std::make_unique<Carapace>(resist,slow);
    }
    else if (randomIndex == 2) {
        double speed = randomDouble(1, speedCoefMax);
        return std::make_unique<Nageoire>(speed);
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
        double detection = randomDouble(detectionMin, detectionMax);
        return std::make_unique<Yeux>(angle,vision,detection);
    }
    else if (randomIndex == 1) {
        double audition = randomDouble(distAuditionMin, distAuditionMax);
        double detect = randomDouble(detectauditMin, detectauditMax);
        return std::make_unique<Oreilles>(audition, detect);
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