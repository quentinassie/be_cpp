#ifndef _MILIEU_H_
#define _MILIEU_H_


#include "UImg.h"
#include "Bestiole.h"

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class BestioleFactory;

class Milieu : public UImg
{

private :
   static const T          white[];

   int                     width, height;
   std::vector<std::shared_ptr<Bestiole>> listeBestioles;
   std::vector<std::shared_ptr<Bestiole>> nouvellesBestioles;

   int num_step;
   std::ofstream fichier;
   
   BestioleFactory& factory;

public :

   Milieu( int _width, int _height, BestioleFactory& _factory);
   ~Milieu( void );

   int getWidth() const { return width; };
   int getHeight() const { return height; };
   std::vector<std::shared_ptr<Bestiole>> getListBestioles() const;

   void step( void );
   
   void addMember(std::shared_ptr<Bestiole> b) {
      b->initCoords(width, height);
      listeBestioles.push_back(b);
   }
   
   int nbVoisins( const Bestiole & b );
   std::vector<std::shared_ptr<Bestiole>> getVoisins(const Bestiole& b);

   std::shared_ptr<Bestiole> getNearestNeighbour(const Bestiole& b);

   void naissanceExterieure();
};


#endif
