#pragma once
#include "Header.h"
#include "Pokemon.h"
#include "Item.h"

//déclaration anticipées
class Pokemon;
class Item;

class Trainer {

public:
	bool m_computer;// si ash est présent ou pas 
	int m_wins;// nb victoire 
	int m_currentPokemon;// nb Pokemon de la partie 
	bool m_allFainted;// si out ou dans la partie 
	std::string m_name;// nom du joeur 
	std::vector<Pokemon*> m_pokemon;// conteneur STL, un vecteur de type ptr de la classe Pokemon
	std::vector<Item*> m_item;// vecteur de type ptr de la classe Item

	Trainer();// constructeur par défat
	Trainer(std::string name);// constructeur comme avec argument le nom 
	~Trainer();// Destructeur 

	// Dessin de trainer 
	void Draw(sf::RenderWindow &window);

	// Vérifie si tous les Pokemons sont out 
	bool AllFainted();

	// Affiche les points de vie 
	void DisplayHealth();

private:
	//Pokemon et Item du joueur 
	static Fire uF1;
	static Fire uF2;
	static Water uW3;
	static Water uW4;
	static Grass uG5;
	static Grass uG6;
	static Item uI1;
	static Item uI2;

	// Pokemon du ash 
	static Fire aF1;
	static Fire aF2;
	static Water aW3;
	static Water aW4;
	static Grass aG5;
	static Grass aG6;

};
