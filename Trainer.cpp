#include "Trainer.h"
#include <iostream>

//Definition du constructeur avec initialisation de ses attibuts
Trainer::Trainer() :
	m_wins(0), 
	m_currentPokemon(0),
	m_name("Anders"),
	m_computer(false),
	m_allFainted(false)
{
}
// de meme pour le constructeur avec argument
Trainer::Trainer(std::string name) :
	m_wins(0),
	m_currentPokemon(0),
	m_name(name), 
	m_computer(true),
	m_allFainted(false)
{
}
//Definition du Destructeur 
Trainer::~Trainer()
{
}

//Dessin train sur l'écran 
void Trainer::Draw(sf::RenderWindow &window) {

	m_pokemon.at(m_currentPokemon) -> Draw(window);// dessin sur l'écran du nombre de pokemon en jeu

}

// Verifie si tous les trainer sont out 
bool Trainer::AllFainted() {

	assert (m_pokemon.size() == 6);

	for (unsigned int i = 0; i < m_pokemon.size(); i++) {
		if(!m_pokemon.at(i) -> m_isFainted) {

			return false;

		}
	}

	return true;

}

// Affiche point de vie de tous les Pokemon sur la cmd 
void Trainer::DisplayHealth() {

	assert (m_pokemon.size() == 6);

	std::cout << m_name << ": " << std::endl << std::endl;
	for (unsigned int i = 0; i < m_pokemon.size(); i++) {
		m_pokemon.at(i) -> displayHealth();
	}
	std::cout << std::endl;

}
