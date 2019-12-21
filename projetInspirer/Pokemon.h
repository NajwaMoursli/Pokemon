#pragma once
#include "Header.h"
#include "DisplayedObject.h"

//La classe Pokemeon hérite de tous les attributs et méthode de la classe DisplayedObject
class Pokemon : public DisplayedObject {

public:
	int m_health;// nb point de vie 
	Type m_type;// un type de Pokemon 
	std::string m_name;
	bool m_isFainted;// si Pokemon out ou encore dans la partie
	
	// Le climat dans l'ensemble du jeu 
	static Weather weather;

	Pokemon(Type type);/// Redefinition du constructeur Pokemon pour les différents type qui en héritent
	Pokemon(Type type, std::string name);// cas de polymorphisme 
	virtual ~Pokemon();// Destructeur 

	// Provoque 20 blessures/dégats
	void attackNormal(Pokemon * opponentPokemon);

	// Répare 20 blessures/dégats
	void heal();

	// Attaque spacial, les dégats dépendants de l'adversaire, du type de Pokemon et du climat
	virtual void specialAttack(Pokemon * opponentPokemon) = 0;

	// Changement du climat selon le type de Pokemon
	virtual void changeWeather() = 0;// initialisation fonction virtuelle 

	// Changement Pokemon s'il est out 
	void changeIfFainted();

	// Utiliser une attaque au hasard 
	void playRandom(Pokemon * opponentPokemon);

	// Affiche les points de vie du Pokemon 
	void displayHealth();

};

// Pokemon type Feu, héritage avec classe Pokemon
class Fire : public Pokemon {

public:
	Fire();
	Fire(std::string name);
	virtual ~Fire();

	void specialAttack(Pokemon * opponentPokemon);
	void changeWeather();

};

//Type Eau 
class Water : public Pokemon {

public:
	Water();
	Water(std::string name);
	virtual ~Water();

	void specialAttack(Pokemon * opponentPokemon);
	void changeWeather();

};

// Type Plante
class Grass : public Pokemon {

public:
	Grass();
	Grass(std::string name);
	virtual ~Grass();

	void specialAttack(Pokemon * opponentPokemon);
	void changeWeather();

};
