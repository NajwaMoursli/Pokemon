#include <cstdlib>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include "global2.hh"
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
        24, 24, 24, 24, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
        24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
        24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
        24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 23, 24, 24, 24, 24, 24, 24, 24, 24,
        24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
        24, 24, 24, 24, 24, 24, 24, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
        24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
        24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
        3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 3,
        3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 3,
        3, 3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 3, 3,
         3, 3, 3, 3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    };

    const int level2[] =
    {
        0, 1, 2, 3, 4, 5, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 23, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 15, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 23, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 15, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 23, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
         3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    };

    // on crée la tilemap avec le niveau précédemment défini
    // int tilePixelsW = 36;
    // int tilePixelsH = 36;

    TileMap map(19,18,684,648,36);
    if (!map.load("tileset_graveyard_tower_interior.png", level)){
        return -1;
	}
	TileMap mapLevel2(19,18,684,648,36);
    if (!mapLevel2.load("tileset_graveyard_tower_interior.png", level2)){
        return -1;
	}

    Character Peter2("sprite.png",0,0,32,32,78,79);
    Peter2.update_index(map);

    sf::Texture fogTexture;
	fogTexture.loadFromFile("fog.png");
	// sf::IntRect rectSpritePeter(65,1,32,32);
	sf::Sprite fog(fogTexture);

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
		    Peter2.update_index(map);

		    bool collision = false;
			if (event.type == sf::Event::KeyPressed){
			    if (event.key.code == sf::Keyboard::S){ //le point (0,0) est en haut a gauche
			    	collision = Peter2.collision(DOWN, map, level, level2);
			    	std::cout << "collisionDOWN = " << collision << std::endl;
			    	Peter2.move_down(collision, clock);
			    }
			    if (event.key.code == sf::Keyboard::Z){
			    	collision = Peter2.collision(UP, map, level, level2);
			    	std::cout << "collisionUP = " << collision << std::endl;
			    	Peter2.move_up(collision, clock);
			    }
			    if (event.key.code == sf::Keyboard::D){
			    	collision = Peter2.collision(RIGHT, map, level, level2);
			    	Peter2.move_right(collision, clock);
			    }
			    if (event.key.code == sf::Keyboard::Q){
			    	collision = Peter2.collision(LEFT, map, level, level2);			    	
			    	Peter2.move_left(collision, clock);
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
				// std::cout << coordinates_to_index(Peter2.get_sprite().) << std::endl;
            }

		}


	renderWindow.clear();
	renderWindow.draw(map);
	renderWindow.draw(mapLevel2);	
	renderWindow.draw(Peter2.m_sprite);
	// renderWindow.draw(fog);
	renderWindow.display();
	}
}	

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