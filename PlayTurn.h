#pragma once
#include "Header.h"

//déclarations anticipées : éviter les références croisées
class Trainer;

class Pokemon;
class Fire;
class Grass;
class Water;
class Item;

//Jouer une partie entière par l'utilisateur et l'ordi 
class PlayTurn {

public:
	// Une partie
	static BattleState PlayTurnWhole(Trainer * user, Trainer * ash, Action action);

	// Jouer une partie par l'utilisateur
	static BattleState PlayTurnUser(Trainer * user, Trainer * ash, Action action);

	// Jouer une partie par l'ordi
	static BattleState PlayTurnAsh(Trainer * user, Trainer * ash);

	// Vérifie si tous les Pokemon sont out 
	static bool CheckIfAllFainted(Trainer * opponentPlayer);

	// Vérifie si besoin de changer de Pokemon si celui d'avant et out 
	static void CheckIfNeedSwitch(Trainer * trainer);

};
