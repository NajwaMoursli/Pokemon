#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"

// using namespace sf;
using namespace std;

void move_down(sf::Clock& clock,sf::Sprite& sprite, sf::IntRect& rectSprite);

int main(int argc, char ** argv){
	sf::RenderWindow renderWindow(sf::VideoMode(304*2, 288*2), "Demo Game");

	sf::Event event;

	/*sprites*/
	sf::Texture texture;
	sf::Texture texturePeter;
	texture.loadFromFile("map.png");
	texturePeter.loadFromFile("sprite.png");

	sf::Sprite sprite(texture);
	sf::IntRect rectSpritePeter(65,1,32,32);
	sf::Sprite spritePeter(texturePeter,rectSpritePeter);
	// cout << "longueur = " << texturePeter.getSize().x;
	// cout << "largeur = " << texturePeter.getSize().y;

	//longueur = 304, largeur = 288 (size de texture, la map)
	sprite.setScale(2,2);
	spritePeter.setScale(1.5,1.5);

/*music*/
	sf::Music music;
	if (!music.openFromFile("pokemon_tower_theme.wav"))
	    return -1; // erreur
	music.setVolume(50);
	music.play();

/*evenements*/
	sf::Clock clock;

	while (renderWindow.isOpen()){
		while (renderWindow.pollEvent(event)){
			if (event.type == sf::Event::EventType::Closed){
		    	renderWindow.close();
			}
			if (event.type == sf::Event::KeyPressed){
			    if (event.key.code == sf::Keyboard::S){ //le point (0,0) est en haut a gauche
			    	move_down(clock,spritePeter,rectSpritePeter);
			    }
			    if (event.key.code == sf::Keyboard::Z){
			    	spritePeter.move(0,-7);
			    }
			    if (event.key.code == sf::Keyboard::D){
			    	spritePeter.move(7,0);
			    }
			    if (event.key.code == sf::Keyboard::Q){
			    	spritePeter.move(-7,0);
			    }
			}

			if (event.type == sf::Event::KeyReleased){
				if(event.key.code == sf::Keyboard::S or event.key.code == sf::Keyboard::Z or event.key.code == sf::Keyboard::D or event.key.code == sf::Keyboard::Q){
				 rectSpritePeter.left = 65;
				 rectSpritePeter.top = 1;
				 spritePeter.setTextureRect(rectSpritePeter);
				 clock.restart();
				}
            }
		}

	renderWindow.clear();
	renderWindow.draw(sprite);
	renderWindow.draw(spritePeter);
	renderWindow.display();
	}
}	



void move_down(sf::Clock& clock,sf::Sprite& sprite, sf::IntRect& rectSprite){
	if(clock.getElapsedTime().asSeconds() > 0.14){
		if((rectSprite.left == 65 and rectSprite.top == 1)or(rectSprite.left == 65 and rectSprite.top == 66)){
	    	rectSprite.left = 64;
			rectSprite.top = 34;
		}
		else if(rectSprite.left == 64 and rectSprite.top == 34){
			rectSprite.left = 65;
			rectSprite.top = 66;
		}
	sprite.setTextureRect(rectSprite);
	sprite.move(0,7);
	clock.restart();
	}
}