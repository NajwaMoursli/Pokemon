#pragma once
#include "Header.h"

class Pokemon;

// Représente un élements du jeu (un joueur peut choisir un élement lors d'un combat)
class Item {

public:
	std::string m_name;
	
	//Point de vie restant
	int m_restoreAmount;

	Item();// Constructeur
	Item(std::string name, int restoreAmount);// Constructeur par copie 
	virtual ~Item();// Destructeur

	void heal(Pokemon * pokemon);

};
