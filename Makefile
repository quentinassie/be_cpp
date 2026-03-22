main : main.cpp Aquarium.o Bestiole.o Milieu.o BestioleFactory.o gregaire.o peureuse.o kamikaze.o prevoyante.o
	g++ -Wall -std=c++11 -o main main.cpp Aquarium.o Bestiole.o Milieu.o BestioleFactory.o gregaire.o peureuse.o kamikaze.o prevoyante.o -I . -lX11 -lpthread

Aquarium.o : Aquarium.h Aquarium.cpp
	g++ -Wall -std=c++11 -c Aquarium.cpp -I .

Bestiole.o : Bestiole.h Bestiole.cpp
	g++ -Wall -std=c++11 -c Bestiole.cpp -I .

Milieu.o : Milieu.h Milieu.cpp
	g++ -Wall -std=c++11 -c Milieu.cpp -I .

BestioleFactory.o : BestioleFactory.h BestioleFactory.cpp SimpleIni.h
	g++ -Wall -std=c++11 -c BestioleFactory.cpp -I .

gregaire.o : Comportement.h gregaire.h gregaire.cpp
	g++ -Wall -std=c++11 -c gregaire.cpp -I .

peureuse.o : Comportement.h peureuse.h peureuse.cpp
	g++ -Wall -std=c++11 -c peureuse.cpp -I .

kamikaze.o : Comportement.h kamikaze.h kamikaze.cpp
	g++ -Wall -std=c++11 -c kamikaze.cpp -I .

Camouflage.o : Accessoire.h Camouflage.h Camouflage.cpp
	g++ -Wall -std=c++11 -c Camouflage.cpp -I .

Carapace.o : Accessoire.h Carapace.h Carapace.cpp
	g++ -Wall -std=c++11 -c Carapace.cpp -I .

Nageoires.o : Accessoire.h Nageoires.h Nageoires.cpp
	g++ -Wall -std=c++11 -c Nageoires.cpp -I .

Oreilles.o : Capteur.h Oreilles.h Oreilles.cpp
	g++ -Wall -std=c++11 -c Oreilles.cpp -I .

Yeux.o : Capteur.h Yeux.h Yeux.cpp
	g++ -Wall -std=c++11 -c Yeux.cpp -I .

prevoyante.o : Comportement.h prevoyante.h prevoyante.cpp
	g++ -Wall -std=c++11 -c prevoyante.cpp -I .
	
clean:
	rm -rf *.o main