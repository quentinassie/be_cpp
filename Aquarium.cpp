#include "Aquarium.h"

#include "Milieu.h"

class BestioleFactory;

Aquarium::Aquarium( int width, int height, int _delay, BestioleFactory& factory ) : CImgDisplay(), delay( _delay )
{

   int         screenWidth = 1280; //screen_width();
   int         screenHeight = 1024; //screen_height();


   cout << "const Aquarium" << endl;

   flotte = new Milieu( width, height, factory);
   assign( *flotte, "Simulation d'ecosysteme" );

   move( static_cast<int>((screenWidth-width)/2), static_cast<int>((screenHeight-height)/2) );

}


Aquarium::~Aquarium( void )
{

   delete flotte;

   cout << "dest Aquarium" << endl;

}


void Aquarium::run(void)
{
   bool mHandled = false;

   while (!is_closed())
   {
      if (is_key()) {
         int k = key();

         if (is_keyESC()) close();

         if ((k == 'p' || k == 'P')) {
            flotte->toggleDebugPerception();
            set_key();
         }

         if ((k == 'm' || k == 'M') && !mHandled) {
            auto liste = flotte->getListBestioles();
            if (!liste.empty()) {
               int i = rand() % liste.size();
               liste[i]->tuer();
            }
            mHandled = true;
            set_key();
         }
      }
      else {
         mHandled = false; // la touche est relâchée
      }

      flotte->step();
      display(*flotte);
      wait(delay);
   }
}
