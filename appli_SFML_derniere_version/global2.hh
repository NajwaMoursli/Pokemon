#ifndef DEF_GLOBAL2
#define DEF_GLOBAL2
#include <iostream>


//Directions possibles d'un deplacement (mouvement vers le haut, vers le bas, vers la droite, vers la gauche, pas de mouvement)
enum Direction{UP, DOWN, RIGHT,	LEFT, NONE};
enum GameState {INTRO, MAP, BATTLEGIRATINA, BATTLEECTOPLASMA, EXIT};
enum BattleState {PLAY, WON, LOST, CHOICE, APPLYATTACK1, APPLYATTACK2, APPLYENEMYATTACK1, APPLYENEMYATTACK2};

#endif
