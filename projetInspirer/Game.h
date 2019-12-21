#pragma once
#include "Header.h"
#include <vector>

// Déclarations anticipées
class DisplayedObject;
class Player;

class Pokemon;
class Fire;
class Grass;
class Water;
class Item;

class Battle;
class Intro;
class Game;

class Trainer;
class PlayTurn;

// Represente le Jeu
class Game
{
public:
	//Fonction début du Jeu 
	static void Start();

private:

	// Statut du Jeu : différentes scènes possibles, utilisation type enum pour simplification
	enum GameState { UNINITIALIZED, INTRO, RULES, ROOM, ROOMIN, ROOMOUT, BATTLE, EXITING };

	// Mouvements des jambes du joeur
	enum Action { STILL, MOVE_LEFT_LEG, MOVE_RIGHT_LEG };

	// Statut du jeu
	static GameState stateOfGame;

	// Fenetre du jeu
	static sf::RenderWindow window;

	// Joueurs
	static Player user;
	static Player ash;

	// Images affichées
	static DisplayedObject roomBackground;
	static DisplayedObject exclamationMark;

	// Fait tourner le jeu jusqu'à que le joueur le quitte
	static void Loop();
	
	// Montre les différentes scènes
	static void ShowIntro();
	static void ShowRules();
	static void ShowRoom();
	static void ShowRoomIn();
	static void ShowRoomOut();
	static void ShowBattle();

	// dessin des joeurs et du fond d'écran
	static void DrawAllRoom();

	// Scenes coupées d'entréée et sorties
	static void In();
	static void Out();

	//Utilisation d'une Sprite sheet  pour imiter le mouvement d'un personnage du jeu
	static void MovePlayer (Direction direction, Player* movingPlayer);
	static void WalkHelper (Direction direction, Action action, Player* movingPlayer);
	static void WalkHelperII (Direction direction, Action action, Player* movingPlayer);

};
