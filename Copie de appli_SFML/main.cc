#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include "tilemap.hh"
#include "character.hh"

// using namespace sf;
using namespace std;

void move_down(sf::Clock& clock,sf::Sprite& sprite, sf::IntRect& rectSprite);
void move_up(sf::Clock& clock,sf::Sprite& sprite, sf::IntRect& rectSprite);
void move_right(sf::Clock& clock,sf::Sprite& sprite, sf::IntRect& rectSprite);
void move_left(sf::Clock& clock,sf::Sprite& sprite, sf::IntRect& rectSprite);
bool tile_is_obstacle(unsigned int i,unsigned int j,const int* tiles,unsigned int width);
bool collision(sf::Sprite sprite,const int* tiles,sf::Vector2u tileSize,unsigned int width);


int main(int argc, char ** argv){
	sf::RenderWindow renderWindow(sf::VideoMode(304*2.25, 288*2.25), "Demo Game");

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
    int tilePixelsW = 36;
    int tilePixelsH = 36;
    TileMap map;
    if (!map.load("tileset_graveyard_tower_interior.png", sf::Vector2u(tilePixelsW,tilePixelsH), level, 19, 18))
        return -1;
    // const int tilesetWidthPixels = map.getSize().x;
    // const int tilesetWidthPixels = map.getSize().y;

    Character Peter2("sprite.png",0,0,32,32,78,79);

	// sf::Texture texturePeter;
	// texturePeter.loadFromFile("sprite.png");
	// sf::IntRect rectSpritePeter(67,33,32,32);
	// sf::Sprite spritePeter(texturePeter,rectSpritePeter);
	// cout << "longueur Peter = " << rectSpritePeter.width << std::endl;
	// cout << "largeur Peter = " << rectSpritePeter.height << std::endl;

	// spritePeter.setPosition(400.f,400.f);
	// spritePeter.setScale(1.5,1.5);

	// bool obstacle = collision(spritePeter,level,sf::Vector2u(tilePixelsW,tilePixelsH),19);
	// if(obstacle){std::cout << 1 << std::endl;}
	// else{std::cout << 0 << std::endl;}

/*music*/
	sf::Music music;
	if (!music.openFromFile("pokemon_tower_theme.wav"))
	    return -1; // erreur
	music.setVolume(50);
	music.play();

/*evenements*/
	sf::Clock clock;
	sf::Event event;
	while (renderWindow.isOpen()){
		while (renderWindow.pollEvent(event)){
			if (event.type == sf::Event::EventType::Closed){
		    	renderWindow.close();
			}
			if (event.type == sf::Event::KeyPressed){
			    if (event.key.code == sf::Keyboard::S){ //le point (0,0) est en haut a gauche
			    	Peter2.move_down(clock);
			    }
			    if (event.key.code == sf::Keyboard::Z){
			    	Peter2.move_up(clock);
			    }
			    if (event.key.code == sf::Keyboard::D){
			    	Peter2.move_right(clock);
			    }
			    if (event.key.code == sf::Keyboard::Q){
			    	Peter2.move_left(clock);
			    }
			}

			if (event.type == sf::Event::KeyReleased){ //sert a remettre le sprite en mode immobile
				if(event.key.code == sf::Keyboard::S){
				 Peter2.set_intRect(67,33);
		 		 Peter2.update_spriteTextureRect();
				 clock.restart();
				}	
				if(event.key.code == sf::Keyboard::Z){
				 Peter2.set_intRect(0,0);
				 Peter2.update_spriteTextureRect();
				 // std::cout << "cgmt : " << Peter2.get_intRect().left << ", " << Peter2.get_intRect().top << std::endl;
				 clock.restart();
				}
				if(event.key.code == sf::Keyboard::D){
				 Peter2.set_intRect(35,0);
		 		 Peter2.update_spriteTextureRect();
				 clock.restart();
				}
				if(event.key.code == sf::Keyboard::Q){
				 Peter2.set_intRect(5,65);
				 Peter2.update_spriteTextureRect();
				 clock.restart();
				}
            }

		}

	renderWindow.clear();
	renderWindow.draw(map);
	// renderWindow.draw(spritePeter);
	// std::cout << "draw end\n";
	std::cout << Peter2.get_intRect().left << ", " << Peter2.get_intRect().top << std::endl;

	renderWindow.draw(Peter2.m_sprite);
	// std::cout << "draw end\n";

	renderWindow.display();
	}
}	



// void move_down(sf::Clock& clock,sf::Sprite& sprite, sf::IntRect& rectSprite){
// 	if(clock.getElapsedTime().asSeconds() > 0.13){ //pour ralentir l'animation, sinon elle est trop rapide
// 		std::cout << rectSprite.left << ", " << rectSprite.top << std::endl; //immobile bas : 67 33
// 		if((rectSprite.left == 67 and rectSprite.top == 33)or(rectSprite.left == 68 and rectSprite.top == 97)){
// 	    	rectSprite.left = 66;
// 			rectSprite.top = 64;
// 		}
// 		else if(rectSprite.left == 66 and rectSprite.top == 64){
// 			rectSprite.left = 68;
// 			rectSprite.top = 97;
// 		}
// 		else{ //si le sprite dans le mauvais sens, on le remet dans le bon sens : le sens du deplacement
// 			rectSprite.left = 67;
// 			rectSprite.top = 33;
// 		}
// 	sprite.setTextureRect(rectSprite);
// 	sprite.move(0,14);
// 	clock.restart();
// 	}
// }

// void move_up(sf::Clock& clock,sf::Sprite& sprite, sf::IntRect& rectSprite){
// 	if(clock.getElapsedTime().asSeconds() > 0.13){ //pour ralentir l'animation, sinon elle est trop rapide
// 		std::cout << rectSprite.left << ", " << rectSprite.top << std::endl;
// 		if((rectSprite.left == 0 and rectSprite.top == 0)or(rectSprite.left == 69 and rectSprite.top == 0)){
// 	    	rectSprite.left = 36;
// 			rectSprite.top = 96;
// 		}
// 		else if(rectSprite.left == 36 and rectSprite.top == 96){
// 			rectSprite.left = 69;
// 			rectSprite.top = 0;
// 		}
// 		else{
// 			rectSprite.left = 0;
// 			rectSprite.top = 0;
// 		}
// 	sprite.setTextureRect(rectSprite);
// 	sprite.move(0,-14);
// 	clock.restart();
// 	}
// }

//  //bas : 67 33 //haut : 0 0 //right : 35 0 //left 5 65
// void move_right(sf::Clock& clock,sf::Sprite& sprite, sf::IntRect& rectSprite){
// 	if(clock.getElapsedTime().asSeconds() > 0.13){ //pour ralentir l'animation, sinon elle est trop rapide
// 		std::cout << rectSprite.left << ", " << rectSprite.top << std::endl;
// 		if((rectSprite.left == 35 and rectSprite.top == 0)or(rectSprite.left == 35 and rectSprite.top == 65)){
// 	    	rectSprite.left = 34;
// 			rectSprite.top = 33;
// 		}
// 		else if(rectSprite.left == 34 and rectSprite.top == 33){
// 			rectSprite.left = 35;
// 			rectSprite.top = 65;
// 		}
// 		else{
// 			rectSprite.left = 35;
// 			rectSprite.top = 0;
// 		}
// 	sprite.setTextureRect(rectSprite);
// 	sprite.move(14,0);
// 	clock.restart();
// 	}
// }

//  //bas : 67 33 //haut : 0 0 //right : 35 0 //left 5 65
// void move_left(sf::Clock& clock,sf::Sprite& sprite, sf::IntRect& rectSprite){
// 	if(clock.getElapsedTime().asSeconds() > 0.13){ //pour ralentir l'animation, sinon elle est trop rapide
// 		std::cout << rectSprite.left << ", " << rectSprite.top << std::endl;
// 		if((rectSprite.left == 5 and rectSprite.top == 65)or(rectSprite.left == 4 and rectSprite.top == 96)){
// 	    	rectSprite.left = 4;
// 			rectSprite.top = 34;
// 		}
// 		else if(rectSprite.left == 4 and rectSprite.top == 34){
// 			rectSprite.left = 4;
// 			rectSprite.top = 96;
// 		}
// 		else{
// 			rectSprite.left = 5;
// 			rectSprite.top = 65;
// 		}
// 	sprite.setTextureRect(rectSprite);
// 	sprite.move(-14,0);
// 	clock.restart();
// 	}
// }


bool tile_is_obstacle(unsigned int i,unsigned int j,const int* tiles,unsigned int width){
	if(tiles[i+j*width] == 3){
		return(true);
	}
	else{
		return(false);
	}
}

//width : largeur de la map en tiles
bool collision(sf::Sprite sprite,const int* tiles,sf::Vector2u tileSize,unsigned int width){
	int i = sprite.getPosition().x/tileSize.x;
	int j = sprite.getPosition().y/tileSize.y;
	std::cout << "i = " << i << ", j = " << j << std::endl;
	return(tile_is_obstacle(i,j,tiles,width));
}

// bool obstacle(Sprite sprite){

// }