#pragma once
#include "Header.h"
#include "Game.h"

// Déclaration anticipée de Trainer et PlayTurn
class Trainer;
class PlayTurn;

// Représentation d'un combat dans le jeu
class Battle {

public:
	// Visualisation du combat
	void show(sf::RenderWindow &window);

private:
	// Status dans le Jeu
		// Perdu, Gagné, Entrain de Jouer 
	static BattleState stateOfGame;

	// Entraineurs
	static Trainer user;
	static Trainer ash;

	// Pokemon du joueur
	static Fire uF1;
	static Fire uF2;
	static Water uW3;
	static Water uW4;
	static Grass uG5;
	static Grass uG6;
	static Item uI1;
	static Item uI2;

	// Ash's Pokemon
	static Fire aF1;
	static Fire aF2;
	static Water aW3;
	static Water aW4;
	static Grass aG5;
	static Grass aG6;

	// Le climat
	static DisplayedObject rain;
	static DisplayedObject sun;
	static DisplayedObject sand;

	//Point de vie 
	static sf::RectangleShape uH;
	static sf::RectangleShape aH;

	// Affiche les points de vie dans l'invite de commande (CMD)
	static void DisplayAllHealth();

	//Dessine tout à l'écran
	static void DrawAll(sf::RenderWindow &window, sf::Sprite * background);

	//Dessine le climat à l'écran
	static void DrawWeather(sf::RenderWindow &window);

	// Initalisation des images, utilisateur et ash
	static void InitalizeLoads();
	static void InitalizeUser();
	static void ResetAsh();

	// Montre les movements sur l'écran
	static void ShowMove(sf::RenderWindow &window, sf::Sprite * background);
	static BattleState chooseMove(sf::RenderWindow &window);

	// Commutation de l'écran
	static void ShowPokemon(sf::RenderWindow &window, sf::Sprite * background);
	static BattleState choosePokemon(sf::RenderWindow &window);

	// Montre les éléments à l'écran
	static void ShowItem(sf::RenderWindow &window, sf::Sprite * background);
	static BattleState choosePotion(sf::RenderWindow &window);

};

