#include "Pokemon.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

// The weather is the same for all pokemon.
	// RAINYDAY donne au type Eau une augmentation de 50% d'attaque spéciale
	// SUNNYDAY donne au type Feu une augmentation de 50% d'attaque spéciale
	// SANDSTORM donne au type Plante une augmentation de 50% d'attaque spéciale
Weather Pokemon::weather;

// Constructeur pour les Pokemon qui n'ont pas de nom
Pokemon::Pokemon(Type type) :
	m_health (100),// Point de vie de départ
	m_type (type),
	m_isFainted (false) {

	if(type == WATER) {
		m_name = "Squirtle";
	} else if (type == GRASS) {
		m_name = "Bulbasaur";
	} else if (type == FIRE) {
		m_name = "Charmander";
	}
}

// Constructeur pour Pokemon avec un nom
Pokemon::Pokemon(Type type, std::string name) :
	m_health (100),
	m_type(type),
	m_name(name),
	m_isFainted (false) {

}

//Destructeur
Pokemon::~Pokemon() {

}

//Attaque normale : perte de 20 points de vie 
void Pokemon::attackNormal (Pokemon * opponentPokemon) {

	opponentPokemon -> m_health = opponentPokemon -> m_health - 20;
	opponentPokemon -> changeIfFainted();

	assert(opponentPokemon -> m_health <= 100 &&
		opponentPokemon -> m_health >= 0);// debugge

}

// Ajout de 20 point de vie 
void Pokemon::heal() {

	m_health += 20;

	if ( m_health > 100 ) {

		m_health = 100;

	}

	assert(m_health <= 100 && m_health >= 0);
}

void Pokemon::changeIfFainted() {

	if(this -> m_health <= 0) {

		m_health = 0;
		m_isFainted = true;

	}

	assert(m_health <= 100 && m_health >= 0);

}

//Mouvemants aléatoires dns le jeu utilisé par ash 
void Pokemon::playRandom(Pokemon * opponentPokemon) {

	srand(time(NULL));
	int randomAttack = (rand() % 4) + 1;

	assert(randomAttack <= 4 && randomAttack >= 1);
	
	if(randomAttack == 1)
		this -> attackNormal(opponentPokemon);
	if(randomAttack == 2)
		this -> specialAttack(opponentPokemon);
	if(randomAttack == 3)
		this -> heal();
	if(randomAttack == 4)
		this -> changeWeather();
}

// Affiche bar de point de vie dans cmd
void Pokemon::displayHealth() {

	std::cout << m_name << " " << m_health << std::endl;

}

// Appel constructeur de Pokemon avec le type Feu en argument
Fire::Fire() 
	: Pokemon(FIRE)
{

}

Fire::Fire(std::string name) 
	: Pokemon(FIRE, name)
{

}

Fire::~Fire () {

}

// L'éfficacité de l'attaque spéciale augmente de 50% si le type de Pokemon correspond à son climat asscocié et de 300% si l'adversaire est affaiblie
void Fire::specialAttack(Pokemon * opponentPokemon) {

	int damage = 10;

	if (weather == SUNNYDAY) {

		damage =  int(damage * 1.50);

	}

	if (opponentPokemon -> m_type == GRASS) {

		damage = (int (damage * 3.0));

	}

	assert(damage <= 45 && damage >= 10);

	opponentPokemon -> m_health = opponentPokemon -> m_health - damage;
	opponentPokemon -> changeIfFainted();

}

void Fire::changeWeather() {

	weather = SUNNYDAY;

}


Water::Water() 
	: Pokemon(WATER)
{

}

Water::Water(std::string name) 
	: Pokemon(WATER, name)
{

}

Water::~Water () {

}

void Water::specialAttack(Pokemon * opponentPokemon) {

	int damage = 10;

	if (weather == RAINDANCE) {

		damage =  int(damage * 1.50);

	}

	if (opponentPokemon -> m_type == FIRE) {

		damage = (int (damage * 3.0));

	}

	assert(damage <= 45 && damage >= 10);

	opponentPokemon -> m_health = opponentPokemon -> m_health - damage;
	opponentPokemon -> changeIfFainted();

}

void Water::changeWeather() {

	weather = RAINDANCE;

}

Grass::Grass() 
	: Pokemon(GRASS)
{

}

Grass::Grass(std::string name) 
	: Pokemon(GRASS, name)
{

}

Grass::~Grass () {

}

void Grass::specialAttack(Pokemon * opponentPokemon) {

	int damage = 10;

	if (weather == SANDSTORM) {

		damage =  int(damage * 1.50);

	}

	if (opponentPokemon -> m_type == WATER) {

		damage = int(damage * 3.0);

	}

	assert(damage <= 45 && damage >= 10);

	opponentPokemon -> m_health = opponentPokemon -> m_health - damage;
	opponentPokemon -> changeIfFainted();

}

void Grass::changeWeather() {

	weather = SANDSTORM;

}
