#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_

#include "Comportement.h"
#include "Capteur.h"
#include "Accessoire.h"
#include "UImg.h"

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Milieu;

class Bestiole
{
private:
   static const double AFF_SIZE;
   static const double MAX_VITESSE;
   static const double LIMITE_VUE;

   static int next;
   int age;
   double taille;
   
   bool personnaliteMultiple=false;
   shared_ptr<Comportement> comportement;
   std::vector<std::unique_ptr<Capteur>> capteurs;
   std::vector<std::unique_ptr<Accessoire>> accessoires;


private:
   int identite;
   int x, y;
   double cumulX, cumulY;
   double orientation;
   double vitesse;
   double vitesseBoost = 0;
   int stepsBoostRestants = 0;
   bool vivante = true;
   double probaCollisionFatale; //collision mortelle
   int ageMax; //âge maximum 


private:
   void bouge( int xLim, int yLim );

public:
   Bestiole( void );
   Bestiole( const Bestiole & b );
   ~Bestiole( void );

   void action( Milieu & monMilieu );
   void draw( UImg & support );

   bool jeTeVois( const Bestiole & b ) const;
   bool collision( const Bestiole & b ) const;

   void initCoords( int xLim, int yLim );

   friend bool operator==( const Bestiole & b1, const Bestiole & b2 );

   void setComportement(std::shared_ptr<Comportement> c) {
      comportement = c;
   }

   std::vector<std::unique_ptr<Capteur>>& getCapteurs() { return capteurs; }

   std::vector<std::unique_ptr<Accessoire>>& getAccessoires() { return accessoires; }

   void setVitesse(double new_vitesse) { vitesse = new_vitesse; };
   void multVitesse(double coef) { vitesse *= coef; };

   void setVitesseMomentanee(double boost, int nbSteps);

   double getVitesse() const {
      return vitesse;
   }

   double getTaille(){return taille;};
   void setTaille(double ntaille){taille = ntaille;};

   static const double getLimiteVue();

   void update(Milieu& m){
      if (comportement) {
         comportement->updateDirection(*this, m);
      }
      
   }

   void setOrientation(double new_orientation){
      orientation = new_orientation;
   }

   double getOrientation() const {
      return orientation;
   }

   int getX() const {
      return x;
   }

   int getY() const {
      return y;
   }

   //collisions :
   bool estVivante() const { return vivante; }
   
   void tuer() { vivante = false; }

   void setProbaCollisionFatale(double p);
   double getProbaCollisionFatale(){return probaCollisionFatale;};


   void setAgeMax(double agemaximum) {ageMax = agemaximum;};

   int getAgeMax(){return ageMax;};

   void setAge(double newage) {age = newage;};

   int getAge(){return age;};

   void activateAccessoires();

   //clonage
   std::shared_ptr<Bestiole> clone() const { return std::make_shared<Bestiole>(*this); }

   //if comportements, accessoires, capteurs
   bool estGregaire();
   bool estPeureuse();
   bool estKamikaze();
   bool estPrevoyante();
   bool estPersMulti();

   bool aCamouflage();
   bool aCarapace();
   bool aNageoires();
   bool aYeux();
   bool aOreilles();
   // getters
   float getCamoCoef() const;


};

#endif