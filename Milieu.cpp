#include "Milieu.h"

#include <cstdlib>
#include <ctime>
#include <cmath>
#include "BestioleFactory.h"


const T    Milieu::white[] = { (T)255, (T)255, (T)255 };


Milieu::Milieu( int _width, int _height , BestioleFactory& _factory) : UImg( _width, _height, 1, 3 ),
                                            width(_width), height(_height), factory(_factory)
{

   cout << "const Milieu" << endl;

   num_step = 0;
   fichier.open("simulation.csv");

    fichier << "num_step,gregaire,peureuse,kamikaze,prevoyante,pers_multi,"
            << "camouflage,carapace,nageoires,yeux,oreilles\n";

   std::srand( time(NULL) );

}


Milieu::~Milieu( void )
{

   cout << "dest Milieu" << endl;

}


void Milieu::step(void)
{
   cimg_forXY(*this, x, y) fillC(x, y, 0, white[0], white[1], white[2]);

   int nbGregaire = 0;
   int nbPeureuse = 0;
   int nbKamikaze = 0;
   int nbPrevoyante = 0;
   int nbPersMulti = 0;

   int nbCamouflage = 0;
   int nbCarapace = 0;
   int nbNageoires = 0;
   int nbYeux = 0;
   int nbOreilles = 0;

   for (auto& b : listeBestioles)
   {
      b->setAge(b->getAge() +1);
      if (b->getAge() >= b->getAgeMax())  // Vieillir et mourir si âge maximum atteint
      {
         b->tuer();
         std::cout<<this<<" est morte de vieillesse"<<endl;
      }
      b->action(*this);

      //collisions
      for (auto& autre : listeBestioles) {
         if (autre != b && autre->estVivante() && b->collision(*autre)) {
   
            double r = static_cast<double>(std::rand()) / RAND_MAX;
   
            if (r < factory.probaCollisionFatale) {
               b->aCamouflage();
               autre->tuer();
            }
   
            b->setOrientation(b->getOrientation() + M_PI);
            break;
         }
      }

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

   // Ajout dans liste des bestioles
   for (auto& b : nouvellesBestioles)
   {
      addMember(b);
   }

   nouvellesBestioles.erase(nouvellesBestioles.begin(), nouvellesBestioles.end());

   //supprime bestioles marquées non vivante
   listeBestioles.erase(
      std::remove_if(listeBestioles.begin(), listeBestioles.end(),
         [](const std::shared_ptr<Bestiole>& b) {
            return !b->estVivante();
         }),
      listeBestioles.end()
   );

   int nb_total = listeBestioles.size();
   
   //recense dans le fichier "simulation" puis dessine les bestioles
   for (auto& b : listeBestioles)
   {
      // Comportements
      if (b->estGregaire())     nbGregaire++;
      if (b->estPeureuse())     nbPeureuse++;
      if (b->estKamikaze())     nbKamikaze++;
      if (b->estPrevoyante())   nbPrevoyante++;
      if (b->estPersMulti())    nbPersMulti++;

      // Accessoires & Capteurs
      if (b->aCamouflage())     nbCamouflage++;
      if (b->aCarapace())       nbCarapace++;
      if (b->aNageoires())      nbNageoires++;
      if (b->aYeux())           nbYeux++;
      if (b->aOreilles())       nbOreilles++;

      b->draw(*this);
   }

   double pctGregaire   = 100.0 * nbGregaire / nb_total;
   double pctPeureuse   = 100.0 * nbPeureuse / nb_total;
   double pctKamikaze   = 100.0 * nbKamikaze / nb_total;
   double pctPrevoyante = 100.0 * nbPrevoyante / nb_total;
   double pctPersMulti  = 100.0 * nbPersMulti / nb_total;

   double pctCamouflage = 100.0 * nbCamouflage / nb_total;
   double pctCarapace   = 100.0 * nbCarapace / nb_total;
   double pctNageoires  = 100.0 * nbNageoires / nb_total;
   double pctYeux       = 100.0 * nbYeux / nb_total;
   double pctOreilles   = 100.0 * nbOreilles / nb_total;

   fichier << num_step << ","
        << pctGregaire << "," << pctPeureuse << "," << pctKamikaze << ","
        << pctPrevoyante << "," << pctPersMulti << ","
        << pctCamouflage << "," << pctCarapace << "," << pctNageoires<< ","
        << pctYeux << "," << pctOreilles << "\n";
   
   num_step++;
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