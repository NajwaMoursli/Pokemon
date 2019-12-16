#pragma once
#include "Header.h"
#include "DisplayedObject.h"
#include <vector>

// Un joeur hérite des attributs et méthodes de la class DisplayedObject pour s'en servir
class Player : public DisplayedObject {

public:
	Player();//Constructeur
	~Player();//Destructeur

	// Mouvements du joueur
	void Move(Direction direction);

	// Dessine le joeur sur l'écran
	void Draw(sf::RenderWindow &window);

	friend class Game;// permet aux membres de cette classe d'accéder à l'attributs privé de la classe Player : m_intRect

private:
	sf::IntRect m_intRect;

};
