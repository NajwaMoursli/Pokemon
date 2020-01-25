#ifndef DEF_GLOBAL2
#define DEF_GLOBAL2
#include <iostream>


//Directions possibles d'un deplacement (mouvement vers le haut, vers le bas, vers la droite, vers la gauche, pas de mouvement)
enum Direction{UP, DOWN, RIGHT,	LEFT, NONE};
enum GameState {INTRO, MAP, BATTLEGIRATINA, BATTLEECTOPLASMA, GAMEOVER, EXIT};
enum BattleState {INTROBATTLE, WON, LOST, RETURNTOMAP, CHOICE, TRANSITION, GOTOGAMEOVER, APPLYATTACK1, APPLYATTACK2, APPLYATTACK3, APPLYENEMYATTACK1, APPLYENEMYATTACK2, APPLYENEMYATTACK3};

#endif
