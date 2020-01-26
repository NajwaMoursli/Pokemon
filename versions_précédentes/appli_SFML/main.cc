#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include "tilemap.hh"

// using namespace sf;
using namespace std;

void move_down(sf::Clock& clock,sf::Sprite& sprite, sf::IntRect& rectSprite);
void move_right(sf::Clock& clock,sf::Sprite& sprite, sf::IntRect& rectSprite);


int main(int argc, char ** argv){
	sf::RenderWindow renderWindow(sf::VideoMode(304*2.25, 288*2.25), "Demo Game");

	sf::Event event;

	/*sprites*/
	sf::Texture texture;
	sf::Texture texturePeter;
	texturePeter.loadFromFile("sprite.png");

	sf::IntRect rectSpritePeter(65,1,32,32);
	sf::Sprite spritePeter(texturePeter,rectSpritePeter);
	// cout << "longueur = " << texturePeter.getSize().x;
	// cout << "largeur = " << texturePeter.getSize().y;

	//longueur = 304, largeur = 288 (size de texture, la map)
	spritePeter.setPosition(200.f,200.f);
	spritePeter.setScale(1.5,1.5);

/*music*/
	// sf::Music music;
	// if (!music.openFromFile("pokemon_tower_theme.wav"))
	//     return -1; // erreur
	// music.setVolume(50);
	// music.play();


/*map*/
	// on définit le niveau à l'aide de numéro de tuiles
    const int level[] =
    {
        3, 3, 3, 3, 3, 3, 24, 24, 24, 24, 24, 24, 24, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 3, 3, 3, 3,
        3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 3,
        3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 3,
        24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
        24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
        24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
        24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
        24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
        24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
        24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
        24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
        24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
        24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
        3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 3,
        3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 3,
        3, 3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 3, 3,
         3, 3, 3, 3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    };


    // on crée la tilemap avec le niveau précédemment défini
    TileMap map;
    if (!map.load("tileset_graveyard_tower_interior.png", sf::Vector2u(36,36), level, 19, 18))
        return -1;

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
			    	move_right(clock,spritePeter,rectSpritePeter);
			    }
			    if (event.key.code == sf::Keyboard::Q){
			    	spritePeter.move(-7,0);
			    }
			}

			if (event.type == sf::Event::KeyReleased){
				
				if(event.key.code == sf::Keyboard::S){
					rectSpritePeter.left = 67;
					rectSpritePeter.top = 33;
					spritePeter.setTextureRect(rectSpritePeter);
					clock.restart();
				}
				else if(event.key.code == sf::Keyboard::N){
					rectSpritePeter.left = 0;
					rectSpritePeter.top = 0;
					spritePeter.setTextureRect(rectSpritePeter);
					clock.restart();
				}
				else if(event.key.code == sf::Keyboard::D){
					rectSpritePeter.left = 35;
					rectSpritePeter.top = 0;
					spritePeter.setTextureRect(rectSpritePeter);
					clock.restart();
				}
				else if(event.key.code == sf::Keyboard::Q){
					rectSpritePeter.left = 5;
					rectSpritePeter.top = 65;
					spritePeter.setTextureRect(rectSpritePeter);
					clock.restart();
				}
            }
		}

	renderWindow.clear();
	renderWindow.draw(map);
	renderWindow.draw(spritePeter);
	renderWindow.display();
	}
}	

//				if(event.key.code == sf::Keyboard::S){
				// 	rectSpritePeter.left = 67;
				// 	rectSpritePeter.top = 33;
				// 	spritePeter.setTextureRect(rectSpritePeter);
				// 	clock.restart();
				// }
				// if(event.key.code == sf::Keyboard::N{
				// 	rectSpritePeter.left = 0;
				// 	rectSpritePeter.top = 0;
				// 	spritePeter.setTextureRect(rectSpritePeter);
				// 	clock.restart();
				// }
				// if(event.key.code == sf::Keyboard::D{
				// 	rectSpritePeter.left = 35;
				// 	rectSpritePeter.top = 0;
				// 	spritePeter.setTextureRect(rectSpritePeter);
				// 	clock.restart();
				// }
				// if(event.key.code == sf::Keyboard::S{
				// 	rectSpritePeter.left = 5;
				// 	rectSpritePeter.top = 65;
				// 	spritePeter.setTextureRect(rectSpritePeter);
				// 	clock.restart();
				// }

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
		else{
			rectSprite.left = 65;
			rectSprite.top = 1;
		}
		// if(event.key.code == sf::Keyboard::S or event.key.code == sf::Keyboard::Z or event.key.code == sf::Keyboard::D or event.key.code == sf::Keyboard::Q){
		// 		 rectSpritePeter.left = 65;
		// 		 rectSpritePeter.top = 1;
	sprite.setTextureRect(rectSprite);
	sprite.move(0,7);
	clock.restart();
	}
}

//  //bas : 67 33 //haut : 0 0 //right : 35 0 //left 5 65
void move_right(sf::Clock& clock,sf::Sprite& sprite, sf::IntRect& rectSprite){
	if(clock.getElapsedTime().asSeconds() > 0.13){ //pour ralentir l'animation, sinon elle est trop rapide
		std::cout << rectSprite.left << ", " << rectSprite.top << std::endl;
		if((rectSprite.left == 35 and rectSprite.top == 0)or(rectSprite.left == 35 and rectSprite.top == 65)){
	    	rectSprite.left = 34;
			rectSprite.top = 33;
		}
		else if(rectSprite.left == 34 and rectSprite.top == 33){
			rectSprite.left = 35;
			rectSprite.top = 65;
		}
		else{
			rectSprite.left = 35;
			rectSprite.top = 0;
		}
	sprite.setTextureRect(rectSprite);
	sprite.move(14,0);
	clock.restart();
	}
}