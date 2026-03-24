#include "Bestiole.h"
#include "Milieu.h"

#include <cstdlib>
#include <cmath>
#include <cstring>

#include <gregaire.h>
#include <peureuse.h>
#include <kamikaze.h>
#include <prevoyante.h>
#include <Camouflage.h>
#include <Carapace.h>
#include <Nageoires.h>
#include <Yeux.h>
#include <Oreilles.h>

const double Bestiole::AFF_SIZE = 8.;
const double Bestiole::MAX_VITESSE = 10.;
const double Bestiole::LIMITE_VUE = 30.;

int Bestiole::next = 0;

Bestiole::Bestiole( void )
{
   identite = ++next;
   //age = rand() % 1001 + 10;
   age = 0;

   cout << "const Bestiole (" << identite << ") par defaut" << endl;

   x = y = 0;
   cumulX = cumulY = 0.;
   orientation = static_cast<double>( rand() ) / RAND_MAX * 2. * M_PI;
   //vitesse = static_cast<double>( rand() ) / RAND_MAX * MAX_VITESSE;
   vitesse = MAX_VITESSE/2;

   //couleur[0] = static_cast<int>( static_cast<double>( rand() ) / RAND_MAX * 230. );
   //ouleur[1] = static_cast<int>( static_cast<double>( rand() ) / RAND_MAX * 230. );
   //couleur[2] = static_cast<int>( static_cast<double>( rand() ) / RAND_MAX * 230. );
}

Bestiole::Bestiole( const Bestiole & b )
{
   identite = ++next;
   age = b.age;

   x = b.x;
   y = b.y;
   cumulX = b.cumulX;
   cumulY = b.cumulY;
   orientation = b.orientation;
   vitesse = b.vitesse;
   vitesseBoost = b.vitesseBoost;
   stepsBoostRestants = b.stepsBoostRestants;
   vivante = b.vivante;

   comportement = b.comportement;

   {
      cout << "const Bestiole (" << identite << ") par copie" << endl;
   
      for (const auto& capteur : b.capteurs) {
         capteurs.push_back(capteur->clone());
      }
   
      for (const auto& accessoire : b.accessoires) {
         accessoires.push_back(accessoire->clone());
      }
   }

}

Bestiole::~Bestiole( void )
{
   cout << "dest Bestiole" << endl;
}

void Bestiole::initCoords( int xLim, int yLim )
{
   x = rand() % xLim;
   y = rand() % yLim;
}

void Bestiole::bouge( int xLim, int yLim)
{

   double vitesseCourante = vitesse;


   if (stepsBoostRestants > 0) {
      vitesseCourante  *= vitesseBoost;
      stepsBoostRestants--;
   }

   double nx, ny;
   double dx = cos( orientation ) * vitesseCourante;
   double dy = -sin( orientation ) * vitesseCourante;
   int cx, cy;

   cx = static_cast<int>( cumulX ); cumulX -= cx;
   cy = static_cast<int>( cumulY ); cumulY -= cy;

   nx = x + dx + cx;
   ny = y + dy + cy;

   if ( (nx < 0) || (nx > xLim - 1) ) {
      orientation = M_PI - orientation;
      cumulX = 0.;
   }
   else {
      x = static_cast<int>( nx );      
      cumulX += nx - x;
   }

   if ( (ny < 0) || (ny > yLim - 1) ) {
      orientation = -orientation;
      cumulY = 0.;
   }
   else {
      y = static_cast<int>( ny );
      cumulY += ny - y;
   }
}

void Bestiole::action(Milieu & monMilieu)
{
   if (!estVivante()) return;
   update(monMilieu);
   bouge(monMilieu.getWidth(), monMilieu.getHeight());
}

void Bestiole::draw(UImg& support)
{
   if (aNageoires()) {
      static bool init = false;
      static CImg<unsigned char> baseRGB;
      static CImg<unsigned char> baseMask;

      if (!init) {
         CImg<unsigned char> nageoiresRGBA("nageoires.png");

         if (nageoiresRGBA.spectrum() >= 3) {
            baseRGB = nageoiresRGBA.get_channels(0, 2).get_resize(taille*20, taille*20);
         } else {
            baseRGB = nageoiresRGBA.get_resize(taille*20, taille*20);
         }

         baseMask = CImg<unsigned char>(baseRGB.width(), baseRGB.height(), 1, 1, 0);
         cimg_forXY(baseRGB, i, j) {
            if (!(baseRGB(i,j,0,0) == 0 &&
                  baseRGB(i,j,0,1) == 0 &&
                  baseRGB(i,j,0,2) == 0)) {
               baseMask(i,j) = 255;
            }
         }

         init = true;
      }

      CImg<unsigned char> img(baseRGB);
      CImg<unsigned char> mask(baseMask);

      float angle = 90.0f - static_cast<float>(orientation * 180.0 / M_PI);
      img.rotate(angle, 1, 0);
      mask.rotate(angle, 1, 0);

      int x0 = x - img.width() / 2;
      int y0 = y - img.height() / 2;

      support.draw_image(x0, y0, 0, 0, img, mask, 1.0f, 255);
   }

   

   double xt = x + cos(orientation) * taille*AFF_SIZE / 2.1;
   double yt = y - sin(orientation) * taille*AFF_SIZE / 2.1;

   support.draw_ellipse(
      x, y, taille*AFF_SIZE, taille*AFF_SIZE / 5.,
      -orientation / M_PI * 180.,
      comportement->getCouleur().data()
   );
   support.draw_circle(
      xt, yt, taille*AFF_SIZE / 2.,
      comportement->getCouleur().data()
   );

   if (aCarapace()) {
      static bool init1 = false;
      static CImg<unsigned char> baseRGB1;
      static CImg<unsigned char> baseMask1;
   
      if (!init1) {
         CImg<unsigned char> carapaceRGBA("carapace.png");
   
         if (carapaceRGBA.spectrum() >= 3) {
            baseRGB1 = carapaceRGBA.get_channels(0, 2).get_resize(taille*12, taille*12);
         } else {
            baseRGB1 = carapaceRGBA.get_resize(taille*12, taille*12);
         }
   
         baseMask1 = CImg<unsigned char>(baseRGB1.width(), baseRGB1.height(), 1, 1, 0);
         cimg_forXY(baseRGB1, i, j) {
            if (!(baseRGB1(i,j,0,0) == 0 &&
                  baseRGB1(i,j,0,1) == 0 &&
                  baseRGB1(i,j,0,2) == 0)) {
               baseMask1(i,j) = 255;
            }
         }
   
         init1 = true;
      }
   
      CImg<unsigned char> img(baseRGB1);
      CImg<unsigned char> mask(baseMask1);
   
      // PNG vertical -> même formule que nageoires
      float angle = 90.0f - static_cast<float>(orientation * 180.0 / M_PI);
      img.rotate(angle, 1, 0);
      mask.rotate(angle, 1, 0);
   
      // décalage vers la queue
      double recul = taille * AFF_SIZE * 0.0;
      int x0 = static_cast<int>(x - std::cos(orientation) * recul - img.width() / 2);
      int y0 = static_cast<int>(y + std::sin(orientation) * recul - img.height() / 2);
   
      support.draw_image(x0, y0, 0, 0, img, mask, 1.0f, 255);
   }

}


bool operator==( const Bestiole & b1, const Bestiole & b2 )
{
   return ( b1.identite == b2.identite );
}


bool Bestiole::jeTeVois( const Bestiole & b ) const
{
   double dist;
   double angle;
   
   dist = std::sqrt( (x - b.x) * (x - b.x) + (y - b.y) * (y - b.y) );
   angle = std::acos( ((x - b.x)*cos(orientation) - (y - b.y)*sin(orientation)) / dist);

   //for (auto& capteur : capteurs){
   //   if (capteur->detect(b, dist, angle)){
   //      return true;
   //   }
   //}

   return ( dist <= LIMITE_VUE );  //à modifier pour retourner "false" quand mis boucle capteurs
}

bool Bestiole::collision( const Bestiole & b ) const{
   double dist;
   dist = std::sqrt( (x - b.x) * (x - b.x) + (y - b.y) * (y - b.y) );

   return (dist <= AFF_SIZE );
}

void Bestiole::setVitesseMomentanee(double boost, int nbSteps){
   vitesseBoost = boost;
   stepsBoostRestants = nbSteps;
}

void Bestiole::setProbaCollisionFatale(double p)
{
   if (p < 0.0) p = 0.0;
   if (p > 1.0) p = 1.0;
   probaCollisionFatale = p;
}

void Bestiole::activateAccessoires() {
   for (auto& accessoire : accessoires) {
       if (accessoire) {
           accessoire->update(this);
       }
   }
}

//type comportements, accessoires, capteurs
bool Bestiole::estGregaire() {
   return dynamic_cast<Gregaire*>(comportement.get()) != nullptr;
}

bool Bestiole::estPeureuse() {
   return dynamic_cast<Peureuse*>(comportement.get()) != nullptr;
}

bool Bestiole::estKamikaze() {
   return dynamic_cast<Kamikaze*>(comportement.get()) != nullptr;
}

bool Bestiole::estPrevoyante() {
   return dynamic_cast<Prevoyante*>(comportement.get()) != nullptr;
}

bool Bestiole::estPersMulti(){
   return personnaliteMultiple; 
}

bool Bestiole::aCamouflage(){
   for (const auto& a : accessoires){
      if (dynamic_cast<Camouflage*>(a.get()) != nullptr){
         return true;
      }
   }
   return false;
}

bool Bestiole::aCarapace(){
   for (const auto& a : accessoires){
      if (dynamic_cast<Carapace*>(a.get()) != nullptr){
         return true;
      }
   }
   return false;
}

bool Bestiole::aNageoires(){
   for (const auto& a : accessoires){
      if (dynamic_cast<Nageoires*>(a.get()) != nullptr){
         return true;
      }
   }
   return false;
}

bool Bestiole::aYeux(){
   for (const auto& c : capteurs){
      if (dynamic_cast<Yeux*>(c.get()) != nullptr){
         return true;
      }
   }
   return false;
}

bool Bestiole::aOreilles(){
   for (const auto& c : capteurs){
      if (dynamic_cast<Oreilles*>(c.get()) != nullptr){
         return true;
      }
   }
   return false;
}

float Bestiole::getCamoCoef() const{
   for (const auto& a : accessoires){
      if (typeid(a) == typeid(Camouflage)){
         Camouflage* camo = dynamic_cast<Camouflage*>(a.get());
         return camo->getCamouflage();
      }
   }
   return 0.0;// Si pas de camouflage, 
}
