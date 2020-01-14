#include <cstdlib>
#include <iostream>
#include <vector>
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
    // int tilePixelsW = 36;
    // int tilePixelsH = 36;

    TileMap map(19,18,684,648,36);
    if (!map.load("tileset_graveyard_tower_interior.png", level)){
        return -1;
	}

	// map.print_coordinates_vertices();

	//VertexArray en 2D (VertexArray 1D a 1368 elements)
	// for(int i = 0;i<18;i++){	
	// 	for(int j = 0;j<76;j++){
	// 		if((j+i*18)%4==0){
	// 			std::cout << "x = " << map.get_vertices()[j+i*18].position.x << ", y = " << map.get_vertices()[j+i*18].position.y << std::endl;
	// 		}
	// 	}
	// }

	// for(int i = 0;i<1368;i++){
	// 	if(i%4==0){
	// 		std::cout << "x = " << map.get_vertices()[i].position.x << ", y = " << map.get_vertices()[i].position.y << std::endl;
	// 	}
	// }

	//exemple point case 0,0
	// std::cout << "\nx0 = " << map.get_vertices()[0+19*0].position.x << ", y0 = " << map.get_vertices()[19*0+0].position.y << std::endl;
	// std::cout << "x1 = " << map.get_vertices()[0+19*0+1].position.x << ", y1 = " << map.get_vertices()[19*0+1].position.y << std::endl;
	// std::cout << "x2 = " << map.get_vertices()[0+19*0+2].position.x << ", y2 = " << map.get_vertices()[19*0+2].position.y << std::endl;
	// std::cout << "x3 = " << map.get_vertices()[0+19*0+3].position.x << ", y3 = " << map.get_vertices()[19*0+3].position.y << std::endl;

    // const int tilesetWidthPixels = map.getSize().x;
    // const int tilesetWidthPixels = map.getSize().y;

    Character Peter2("sprite.png",0,0,32,32,78,79);

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
				// std::cout << coordinates_to_index(Peter2.get_sprite().) << std::endl;
            }

		}



	renderWindow.clear();
	renderWindow.draw(map);
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

//donne l'indice du tile dans lequel se trouve un point :
// - int x, int y : coordonnees d'un point
// - int width : largeur 
// std::vector<unsigned int> coordinates_to_index(unsigned int x,unsigned int y,TileMap map){
// 	unsigned int indX = x/map.get_tileSize();
// 	unsigned int indY = y/map.get_tileSize();
// 	std::vector<unsigned int> ind;
// 	ind.push_back(indX);
// 	ind.push_back(indY);
// 	std::cout << "indx = " << indX << ", indy = " << indY << std::endl;
// 	return(ind);
// }

// bool obstacle(Sprite sprite){

// }