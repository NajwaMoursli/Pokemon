#pragma once
#include "Rules.h"

// Affichage Regles
void Rules::show(sf::RenderWindow &window)
{
	// Chargement image correspondante
	sf::Texture texture;
	if(texture.loadFromFile("images/Rules.png") != true) {
		return;
	}

	sf::Sprite sprite(texture);// création sprite à partir de la texture
	window.draw(sprite);// dessin de la fenetre à partir de la sprite sheet
	window.display();// affichage de la fenetre 

	sf::Event currentEvent;// objet event
	while(true)
	{
		while(window.pollEvent(currentEvent))// ajout des evenements dans la queue 
		{
			
			if(currentEvent.type == sf::Event::Closed) { 
				exit(0);
			}

			if(currentEvent.type == sf::Event::EventType::KeyPressed 
				|| currentEvent.type == sf::Event::EventType::Closed)
			{
				return;
			}
		}
	}
}
