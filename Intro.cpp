#pragma once
#include "Intro.h"

void Intro::show(sf::RenderWindow &window)
{
	// Utilisation de texture pour utiliser Sprite Sheet
	sf::Texture texture;
	if(texture.loadFromFile("images/Intro.png") != true) { // si chargement de l'image OK 
		return;
	}

	sf::Sprite sprite(texture);//création texture qui permet utilisation Sprite Sheet
	window.draw(sprite);// Dessin de la sprite sur la fenetre crée
	window.display();//Affichage de la fentre 

	sf::Event currentEvent;// actions clavier définissant comment jouer (les evenements), ajouter à la queue, ici création evenement
	while(true)
	{
		while(window.pollEvent(currentEvent))// si queue vide retourne 0 sinon cela copie le premier evenement dans la queue dans l'objet event crée passé en argument
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
