#pragma once
#include "Header.h"

// Represente un objet affiché à l'écran 
class DisplayedObject {

public:

	// coordonnée (x,y) dans un plan de l'objet (pour le localiser)
	float m_x;
	float m_y;

	DisplayedObject();//Constructeur par défaut
	virtual ~DisplayedObject();//Destructeur

	// Chargement d'objet à partir d'un fichier
	virtual void Load(std::string filename);

	// Dessin de l'objet
	virtual void Draw(sf::RenderWindow &window);

	// Nouvelle position (donc changement de coordonnée) de l'objet par méthode Set
	virtual void SetPosition(float x, float y);

protected:
	bool m_loaded;
	sf::Sprite m_sprite;

private:
	sf::Texture m_texture;
	std::string m_filename;
	
};
