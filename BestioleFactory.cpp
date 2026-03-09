#include "BestioleFactory.h"
#include <iostream>
#include <random>

BestioleFactory::BestioleFactory(){
    std::cout<< "BestioleFactory created" << std::endl;
    comportement_dict={
        {"grégaire", std::shared_ptr<Comportement>(new Gregaire())},
        {"peureuse", std::shared_ptr<Comportement>(new Peureuse())},
        {"kamikaze", std::shared_ptr<Comportement>(new Kamikaze())},
        {"prévoyante", std::shared_ptr<Comportement>(new Prevoyante())},
    }
}

BestioleFactory::~BestioleFactory(){
    std::cout<< "BestioleFactory destroyed" << std::endl;
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