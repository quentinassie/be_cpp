#include "../Camouflage.h"
#include "../Accessoire.h"
#include "../BestioleFactory.h"
#include "../Bestiole.h"
#include "../Yeux.h"
#include "../Oreilles.h"
#include <cassert>

void test_clone() {
    // test de la méthode clone de Camouflage
    Camouflage camo(0.5);
    std::unique_ptr<Accessoire> clone_camo = camo.clone();
    assert(clone_camo != nullptr);
    assert(dynamic_cast<Camouflage*>(clone_camo.get())->getCamouflage() == 0.5);
}


void test_camouflage_in_bestiole() {
    // Créer une factory avec une configuration simple
    BestioleFactory factory("../config.ini");
    // créer une bestiole manuellement
    auto b = std::make_shared<Bestiole>();
    auto camo = std::unique_ptr<Camouflage>(new Camouflage(0.5));
    b->getAccessoires().push_back(std::move(camo));
    assert(b->aCamouflage());   
    assert(b->getCamoCoef() == 0.5); // vérifier que le coefficient de camouflage est correctement retourné
}

void test_detection() {
    BestioleFactory factory("../config.ini");
        auto b1 = std::make_shared<Bestiole>();
        auto b2 = std::make_shared<Bestiole>();
        auto b3 = std::make_shared<Bestiole>();

        auto camo= std::unique_ptr<Camouflage>(new Camouflage(1.0));// Camouflage complet
        b2->getAccessoires().push_back(std::move(camo));
        
        auto yeux = std::unique_ptr<Yeux>(new Yeux(100.0, 30.0, 0.7)); 
        b1->getCapteurs().push_back(std::move(yeux));

        auto oreille = std::unique_ptr<Oreilles>(new Oreilles(30.0, 0.7));
        // Placer b2 à une distance de 20 unités de b1
        b2->setX(20.0);

        assert(b1->jeTeVois(*b2)==false); // b1 ne devrait pas voir b2 à cause du camouflage complet
        assert(b1->jeTeVois(*b3)==true); // b1 devrait voir b3 qui n'a pas de camouflage
        assert(b3->jeTeVois(*b2)==false); // b3 devrait voir b2 qui a du camouflage
}



int main() {
    test_clone();
    std::cout << "test_clone passed!" << std::endl;
    test_camouflage_in_bestiole();
    std::cout << "test_camouflage_in_bestiole passed!" << std::endl;
    test_detection();
    std::cout << "test_detection passed!" << std::endl;
    return 0;
}