# Simulation Bestioles - Écosystème Virtuel

Simulation d'un écosystème de bestioles évoluant dans un aquarium 2D avec comportements, gadgets, naissances, morts et collisions.

---

## Table des Matières

- [Description](#description)
- [Architecture](#architecture)
- [Fonctionnalités Implémentées](#fonctionnalités-implémentées)
- [Installation et Compilation](#installation-et-compilation)
- [Configuration](#configuration)
- [Tests](#tests)
- [Structure du Projet](#structure-du-projet)

---

## Description
Ce projet s’inscrit dans le cadre d’un Bureau d’Étude (BE) dont l’objectif est de faire évoluer une simulation existante d’écosystème en y intégrant de nouvelles fonctionnalités (capteurs, accessoires, comportements avancés) et en appliquant des design patterns pour une architecture modulaire et extensible.

La simulation initiale permettait à des **bestioles** de se déplacer dans un aquarium en rebondissant sur les parois. Le travail consiste à enrichir ce modèle avec :

- des comportements dynamiques (grégaire, peureuse, kamikaze, prévoyante, personnalité multiple) 
- des capteurs (yeux, oreilles) qui conditionnent la perception de l’environnement 
- des accessoires (nageoires, carapace, camouflage) modifiant les capacités de déplacement et de survie 
- une gestion avancée de la population (naissance, clonage, mort par vieillesse ou collision) 
- une interface graphique différenciant les types de bestioles 
- une journalisation des statistiques de population

---

## Architecture

### 1- Design Patterns

**Stratégie**: L’interface Comportement définit updateDirection. Les classes Gregaire, Peureuse, Kamikaze, Prevoyante implémentent des stratégies de déplacement distinctes.

### 2- Classes principales

**Aquarium** : hérite de CImgDisplay, gère la boucle d’affichage et le timing.

**Milieu** : contient la liste des bestioles, gère les étapes (vieillissement, collisions, naissances), écrit les statistiques.

**Bestiole** : entité centrale (position, orientation, vitesse, âge, comportement, capteurs, accessoires).

**Comportement** : classe abstraite implémentée par les cinq comportements concrets.

**Capteur** : interface pour les capteurs (Yeux et Oreilles).

**Accessoire** : interface pour les accessoires (Nageoires, Carapace et Camouflage).

**BestioleFactory** : fabrique de bestioles paramétrée par config.ini.

---

## Fonctionnalités Implémentées

### 1- Comportements Dynamiques 

**Grégaire**: Aligne sa direction sur la direction moyenne des bestioles détectées.	 (gregaire.cpp)

**Peureuse**: Fuit les voisins en accélérant temporairement. (peureuse.cpp)

**Kamikaze**: Se dirige vers la bestiole la plus proche pour provoquer une collision.	(kamikaze.cpp)

**Prévoyante**: Anticipe les trajectoires des voisins pour éviter les collisions futures.	(prevoyante.cpp)

**Personnalité multiple**: change de personnalités aléatoirement au cours du temps.

### 2- Capteurs

Deux capteurs permettent aux bestioles de percevoir leur environnement :

**Yeux** :  Distance vision δᵥ, Angle de vision α,  Capacité de détection γᵥ ∈ [γᵥᵐⁱⁿ, γᵥᵐᵃˣ], Bestiole A détecte la Bestiole B si γᵥ(A) > ψ(B).

**Oreilles** :  Distance audition δₐ, Capacité de détection γₐ ∈ [γₐᵐⁱⁿ, γₐᵐᵃˣ], Bestiole A détecte la Bestiole B si γₐ(A) > ψ(B).

- Les bornes sont définies globalement dans config.ini ; chaque bestiole reçoit des valeurs aléatoires dans ces intervalles.
- Chaque bestiole peut avoir 0 à plusieurs capteurs, avec au plus un de chaque.

### 3- Accessoires

**Camouflage** : réduit la probabilité de détection.

**Carapace** : réduit la vitesse et augmente la résistance aux collisions.

**Nageoires** : augmente temporairement la vitesse.

- Chaque bestiole peut avoir 0 à plusieurs accessoires, avec au plus un de chaque.

### 4- Gestion de la Population

**Naissance spontanée** : Taux de naissance spontanée configurable dans le fichier config.ini. Une nouvelle bestiole est créée aléatoirement selon la distribution des comportements.

**Clonage** : Probabilité de clonage configurable dans le fichier config.ini. Une bestiole se clone (copie profonde) et le clone naît avec un âge nul.


**Vieillissement** : Âge maximal configurable dans le fichier config.ini. La bestiole meurt quand son âge atteint ageMax.

**Collision** : Probabilité de mort par collision configurable dans le fichier config.ini. En cas de survie, rebond à 180°.

### 5- Statistiques 

Le fichier simulation.csv est généré à chaque pas de temps. Il contient :

- Numéro du pas

- Pourcentage de bestioles de chaque comportement (grégaire, peureuse, kamikaze, prévoyante, pers_multi)

- Pourcentage de bestioles possédant chaque accessoire (camouflage, carapace, nageoires)

- Pourcentage de bestioles possédant chaque capteur (yeux, oreilles)

Les colonnes sont écrites à chaque appel de Milieu::step().

### 6- Interface Graphique 
- Fenêtre d’affichage avec l’aquarium (640×480 par défaut).

- Les bestioles sont dessinées sous forme d’ellipse orientée, avec une tête circulaire et une taille initialisée aléatoirement.

- La couleur dépend du comportement :

**Grégaire** : rose clair

**Peureuse** : bleu clair

**Kamikaze** : rouge

**Prévoyante** : vert

**Personnalité multiple** : couleur qui change au cours du temps

### 7- Événements extérieurs / Contrôles clavier

L’utilisateur peut interagir avec la simulation au clavier afin de provoquer certains événements extérieurs :

- **P** : active ou désactive l’affichage debug des perceptions.
- **M** : tue une bestiole choisie aléatoirement.
- **N** : fait naître une nouvelle bestiole aléatoire.
- **C** : change aléatoirement le comportement d’une bestiole existante.

Ces événements permettent de modifier dynamiquement la population pendant l’exécution de la simulation.

---

## Installation et Compilation

### Prérequis
- Compilateur C++11 (g++ ≥ 4.8, clang)

- Bibliothèque CImg 

- SimpleIni 

### Compilation

Un Makefile est fourni:
- make          # Compile et produit l'exécutable main
- make clean    # Supprime les fichiers objets et l'exécutable

### Exécution

./main

---

## Configuration
Tous les paramètres de la simulation sont configurés dans le fichier config.ini

[population]

nombre = 1 # Nombre initial de la population

[population.comportements] # ditribution des comprtements

gregaire = 0.4

peureuse = 0.1

prevoyante = 0.1

kamikaze = 0.1

personnalite_multiple = 0.0

[general]

naissance = 0.02 # Taux de naissance spontanée

age_max = 800

clonage = 0.0004 # Probabilité de clonage

freq_mort = 0.0

// Caractéristiques des Yeux

[angle_vision]

min = 20.0

max = 120.0

[distance_vision]

min = 5.0

max = 80.0

//Caractéristiques des Oreilles

[distance_audition]

min = 30.0

max = 100.0

// Caractéristiques des Accessoires

[camouflage]

min = 0.3

max = 1.0

[carapace]

slow = 0.3

death = 3.0

[nageoires]

max=1.8

[detect_vision]

min = 0.0

max = 1.0

[detect_audition]

min = 0.0

max = 1.0

[collision]

defaut = 0.4 # Probabilité de mort par collision

**Remarques**:

- Le detect_vision et le detect_audition minimal et maximal doivent être entre 0 et 1.
- Le coefficient multiplicateur maximal pour les nageoires doit être supérieur à 1.
- La valeur maximale pour la probabilité de mort par collision doit être supérieur à 1.
- La capacité de camouflage minimale et maximale doivent être entre 0 et 1. 

---

## Tests
### Tests de la classe Camouflage
Des tests unitaires ont été développés pour valider le bon fonctionnement de l’accessoire Camouflage.

#### Objectifs des tests :

- Vérifier le clonage d’un accessoire Camouflage.

- Vérifier l’ajout d’un camouflage à une bestiole.

- Tester l’effet du camouflage sur la détection.

---

## Structure du projet
```
├── main.cpp                     # Point d’entrée
├── Makefile                     # Compilation
├── config.ini                   # Configuration de la simulation
├── Aquarium.h / .cpp            # Fenêtre et boucle principale
├── Milieu.h / .cpp              # Environnement et logique de simulation
├── Bestiole.h / .cpp            # Entité bestiole
├── BestioleFactory.h / .cpp     # Fabrique de bestioles
├── Comportement.h               # Interface des comportements (Strategy)
├── gregaire.h / .cpp            # Comportement grégaire
├── peureuse.h / .cpp            # Comportement peureux
├── kamikaze.h / .cpp            # Comportement kamikaze
├── prevoyante.h / .cpp          # Comportement prévoyant
├── Capteur.h                    # Interface des capteurs
├── Yeux.h / .cpp                # Capteur Yeux 
├── Oreilles.h / .cpp            # Capteur Oreilles 
├── Accessoire.h                 # Interface des accessoires
├── Camouflage.h / .cpp          # Accessoire Camouflage 
├── Carapace.h / .cpp            # Accessoire Carapace 
├── Nageoires.h / .cpp           # Accessoire Nageoires 
├── UImg.h                       # Wrapper pour CImg
├── CImg.h                       # Bibliothèque graphique CImg
├── SimpleIni.h                  # Lecteur de fichiers INI
├── nageoires.png                # Image pour l’accessoire Nageoires
├── tests/
│   ├── Makefile                 # Compilation des tests
│   ├── test_camouflage.cpp      # Tests unitaires pour Camouflage
└── simulation.csv               # Fichier de statistiques 
```
