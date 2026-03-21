#include "Milieu.h"

#include <cstdlib>
#include <ctime>


const T    Milieu::white[] = { (T)255, (T)255, (T)255 };


Milieu::Milieu( int _width, int _height ) : UImg( _width, _height, 1, 3 ),
                                            width(_width), height(_height)
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
      b->draw(*this);
   }
}

int Milieu::nbVoisins(const Bestiole& b)
{
   int nb = 0;

   for (auto& autre : listeBestioles)
      if (!(*autre == b) && b.jeTeVois(*autre))
         ++nb;

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