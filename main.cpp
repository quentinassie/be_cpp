#include "Aquarium.h"
#include "Milieu.h"
#include "Bestiole.h"
#include "BestioleFactory.h"

#include <iostream>
#include <memory>

using namespace std;


int main()
{
   Aquarium ecosysteme(640, 480, 30);
   BestioleFactory factory("config.ini");

   for (int i = 0; i < factory.nombrePopulationInitiale; ++i)
   {
      auto b = factory.createBestioleAleatoire();
      ecosysteme.getMilieu().addMember(b);
   }

   ecosysteme.run();

   return 0;
}