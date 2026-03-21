#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_

#include "Comportement.h"
#include "UImg.h"

#include <iostream>
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
   shared_ptr<Comportement> comportement;
   // std::vector<std::unique_ptr<Capteur>> capteurs;
   // std::vector<std::unique_ptr<Accessoire>> accessoires;


private:
   int identite;
   int x, y;
   double cumulX, cumulY;
   double orientation;
   double vitesse;
   double vitesseBoost = 0;
   int stepsBoostRestants = 0;

private:
   void bouge( int xLim, int yLim );

public:
   Bestiole( void );
   Bestiole( const Bestiole & b );
   ~Bestiole( void );

   void action( Milieu & monMilieu );
   void draw( UImg & support );

   bool jeTeVois( const Bestiole & b ) const;

   void initCoords( int xLim, int yLim );

   friend bool operator==( const Bestiole & b1, const Bestiole & b2 );

   void setComportement(std::shared_ptr<Comportement> c) {
      comportement = c;
   }

   void setVitesse(double new_vitesse){
      vitesse = new_vitesse;
   }

   void setVitesseMomentanee(double boost, int nbSteps);

   double getVitesse() const {
      return vitesse;
   }

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
};

#endif