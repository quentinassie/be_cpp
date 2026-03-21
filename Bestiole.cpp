#include "Bestiole.h"
#include "Milieu.h"

#include <cstdlib>
#include <cmath>
#include <cstring>

const double Bestiole::AFF_SIZE = 8.;
const double Bestiole::MAX_VITESSE = 10.;
const double Bestiole::LIMITE_VUE = 30.;

int Bestiole::next = 0;

Bestiole::Bestiole( void )
{
   identite = ++next;
   age = rand() % 1001 + 10;

   cout << "const Bestiole (" << identite << ") par defaut" << endl;

   x = y = 0;
   cumulX = cumulY = 0.;
   orientation = static_cast<double>( rand() ) / RAND_MAX * 2. * M_PI;
   //vitesse = static_cast<double>( rand() ) / RAND_MAX * MAX_VITESSE;
   vitesse = MAX_VITESSE/1.5;

   //couleur[0] = static_cast<int>( static_cast<double>( rand() ) / RAND_MAX * 230. );
   //ouleur[1] = static_cast<int>( static_cast<double>( rand() ) / RAND_MAX * 230. );
   //couleur[2] = static_cast<int>( static_cast<double>( rand() ) / RAND_MAX * 230. );
}

Bestiole::Bestiole( const Bestiole & b )
{
   identite = ++next;
   age = b.age;

   cout << "const Bestiole (" << identite << ") par copie" << endl;

   x = b.x;
   y = b.y;
   cumulX = b.cumulX;
   cumulY = b.cumulY;
   orientation = b.orientation;
   vitesse = b.vitesse;

   comportement = b.comportement;
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

void Bestiole::bouge( int xLim, int yLim )
{
   double nx, ny;
   double dx = cos( orientation ) * vitesse;
   double dy = -sin( orientation ) * vitesse;
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

void Bestiole::action( Milieu & monMilieu )
{
   update(monMilieu);
   bouge(monMilieu.getWidth(), monMilieu.getHeight());
}

void Bestiole::draw( UImg & support )
{
   double xt = x + cos( orientation ) * AFF_SIZE / 2.1;
   double yt = y - sin( orientation ) * AFF_SIZE / 2.1;

   //std::cout<<"couleur du comportement"<<comportement->getCouleur()[0]<<endl;

   support.draw_ellipse( x, y, AFF_SIZE, AFF_SIZE / 5., -orientation / M_PI * 180., comportement->getCouleur().data() );
   support.draw_circle( xt, yt, AFF_SIZE / 2., comportement->getCouleur().data() );
}

bool operator==( const Bestiole & b1, const Bestiole & b2 )
{
   return ( b1.identite == b2.identite );
}

bool Bestiole::jeTeVois( const Bestiole & b ) const
{
   double dist;
   dist = std::sqrt( (x - b.x) * (x - b.x) + (y - b.y) * (y - b.y) );
   return ( dist <= LIMITE_VUE );
}