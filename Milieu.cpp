#include "Milieu.h"

#include <cstdlib>
#include <ctime>
#include "BestioleFactory.h"


const T    Milieu::white[] = { (T)255, (T)255, (T)255 };


Milieu::Milieu( int _width, int _height , BestioleFactory& _factory) : UImg( _width, _height, 1, 3 ),
                                            width(_width), height(_height), factory(_factory)
{

   cout << "const Milieu" << endl;

   std::srand( time(NULL) );

}


Milieu::~Milieu( void )
{

   cout << "dest Milieu" << endl;

}


void Milieu::step(void)
{
   cimg_forXY(*this, x, y) fillC(x, y, 0, white[0], white[1], white[2]);

   for (auto& b : listeBestioles)
   {
      b->action(*this);

      //clonage automatique
      if (b->estVivante() && static_cast<double>(std::rand()) / RAND_MAX < factory.probaClonage)
      {
         auto clonee = b->clone();
         //clonee->initCoords(width, height);
         nouvellesBestioles.push_back(clonee);
      }
   }

   // Naissance spontanée dans le vivarium
   if (static_cast<double>(std::rand()) / RAND_MAX < factory.tauxNaissanceGlobal)
   {
      auto neeBestiole = factory.createBestioleAleatoire();
      neeBestiole->initCoords(width, height);
      nouvellesBestioles.push_back(neeBestiole);
      std::cout<<"naissance d'une bestiole :"<<neeBestiole<<endl;
   }

   // Ajout dan liste des bestioles
   for (auto& b : nouvellesBestioles)
   {
      addMember(b);
      nouvellesBestioles.erase(nouvellesBestioles.begin(), nouvellesBestioles.end());
   }

   //supprime bestioles marquées non vivante
   listeBestioles.erase(
      std::remove_if(listeBestioles.begin(), listeBestioles.end(),
         [](const std::shared_ptr<Bestiole>& b) {
            return !b->estVivante();
         }),
      listeBestioles.end()
   );

   for (auto& b : listeBestioles)
   {
      b->draw(*this);
   }

}

int Milieu::nbVoisins(const Bestiole& b)
{
   int nb = 0;

   for (auto& autre : listeBestioles){
      if (!(*autre == b) && b.jeTeVois(*autre)){
         ++nb;
      }
   }
   return nb;
}



std::vector<std::shared_ptr<Bestiole>> Milieu::getVoisins(const Bestiole& b)
{
   std::vector<std::shared_ptr<Bestiole>> voisins;

   for (auto& autre : listeBestioles)
   {
      if (!(*autre == b) && b.jeTeVois(*autre))
      {
         voisins.push_back(autre);
      }
   }

   return voisins;
}


std::vector<std::shared_ptr<Bestiole>> Milieu::getListBestioles() const{
   return listeBestioles;
}



shared_ptr<Bestiole> Milieu ::getNearestNeighbour(const Bestiole& b){

   double nearest = 100000;
   std::shared_ptr<Bestiole> target;

   for (auto& other : listeBestioles) {

      if (!(*other == b)) {
         double distance = std::sqrt(
            (other->getX() - b.getX()) * (other->getX() - b.getX()) +
            (other->getY() - b.getY()) * (other->getY() - b.getY())
        );

        if (distance < nearest){
         nearest = distance;
         target = other;
        }


      }
  }

  return target;
}

void Milieu::naissanceExterieure(){
   auto b = factory.createBestioleAleatoire();
   b->initCoords(width, height);
   addMember(b);
}