# Projet de C++ en deuxième année d'école d'ingénieur

## Mini-jeu Pokemon dans la Tour Pokemon de Lavanville
Il s'agit d'un projet libre en équipe : programmer une application en C++ avec la programmation orientée objet en lien avec le thème de la fumée (sujet laissé libre aux élèves). Nous avons choisi de coder un mini-jeu Pokemon en nous inspirant de la Tour Pokemon de Lavanville où l'on peut trouver de la fumée dans le décor.

## Fichiers
* **global.hh, global.cc, global2.hh, global2.cc** : déclarent et définissent des constantes, des enum et des surcharges d'opérateurs.
* **move.hh, move.cc** : déclarent et définissent la classe Move ainsi que ses classes filles (héritage).
* **pokemon.hh, pokemon.cc** : déclarent et définissent la classe Pokemon.
* **character.hh, character.cc** : déclarent et définissent la classe Character (la classe pour le personnage)
* **picture.hh, picture.cc** : déclarent et définissent la classe Picture (la classe pour les images affichées à l'écran) 
* **text.hh, text.cc** : déclarent et définissent la classe Text 
* **tilemap.hh, tilemap.cc** : déclarent et définissent la classe Tilemap (la classe pour la carte, la construire couche par couche, élément par élément)
* **game.hh, game.cc** : déclarent et définissent la classe Game (la classe pour gérer les événements du jeu) 
* **main.cc** : est le premier source compilé, il sert à lancer le jeu.
* **Pokemon.exe** : est l'exécutable qu'on peut lancer pour commencer à jouer au jeu