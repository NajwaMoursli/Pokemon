#pragma once
#include "Intro.h"

void Intro::show(sf::RenderWindow &window)
{
	// Utilisation de texture pour utiliser Sprite Sheet
	sf::Texture texture;
	if(texture.loadFromFile("images/Intro.png") != true) {
		return;
	}

	sf::Sprite sprite(texture);
	window.draw(sprite);
	window.display();

	sf::Event currentEvent;
	while(true)
	{
		while(window.pollEvent(currentEvent))
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
