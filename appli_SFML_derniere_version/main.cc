#include <cstdlib>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include "global2.hh"
#include "tilemap.hh"
#include "character.hh"
#include "game.hh"

// using namespace sf;
using namespace std;

// bool tile_is_obstacle(unsigned int i,unsigned int j,const int* tiles,unsigned int width);

int main(int argc, char ** argv){
	sf::RenderWindow renderWindow(sf::VideoMode(304*2.25, 288*2.25), "Demo Game");

/*creation de la map*/
	// creation de la grille de la couche 1 (le sol)
    const int level[] =
    {
        3, 3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3, 3,
        3,  3,  3,  3, 3,  3,  3,  24,  3,  3,  3,  24,  3,  3, 3,  3,  3,  3, 3,
        3,  3,  3,  3,  3, 24, 24, 24,  24, 24, 24, 24, 24, 24, 3,  3,  3, 3, 3,
        3, 3, 24, 24, 24, 24, 24, 24, 24,  56, 57, 58, 24, 24, 24, 24, 24, 3, 10,
        24, 3, 24, 24, 24, 24, 24, 24,  24, 64, 65, 66, 24, 24, 24, 24, 24, 24, 10,
        24, 24, 24, 24, 24, 24, 24, 24, 24, 72, 73, 74, 24, 24, 24, 24, 24, 24, 10,
        24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 18,
        24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
        3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
        3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
        3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
        3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 3,
        3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 3,
        3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 3,
        3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 3, 3,
        3, 3, 3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 3, 3,
        3, 3, 3, 3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 3, 3, 3,
         3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    };

    // creation de la grille de la couche 2 (les objets, obstacles, exemple : murs, plots ...)
    const int level2[] =
    {
		3, 3,  3,  3,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  3,  3,  3, 3,
        3,  0,  1,  1, 16,  9,  9,  9,  9,  9,  9,  9,  9,  9, 18,  1,  1,  2, 3,
        3,  8,  9,  9,  9, 3, 3, 3,  4, 3, 3, 3, 4, 3, 9,  9,  9, 18, 2,
        1, 16, 3, 3, 3, 3, 3, 3, 12, 3, 3, 3, 12, 3, 3, 3, 3, 9, 10,
        9, 9, 3, 3, 3, 3, 3, 3,  20, 3, 3, 3, 20, 3, 3, 3, 3, 3, 10,
        23, 3, 3, 3, 3, 3, 3, 3, 23, 3, 3, 3, 23, 3, 3, 3, 3, 3, 10,
        23, 3, 3, 3, 23, 3, 23, 23, 23, 3, 3, 23, 23, 3, 3, 3, 3, 3, 18,
        23, 3, 3, 3, 3, 23, 3, 3, 3, 3, 3, 3, 23, 3, 3, 3, 3, 23, 9,
        3, 3, 3, 3, 23, 23, 23, 3, 3, 3, 3, 23, 23, 3, 3, 23, 23, 23, 3,
        3, 3, 3, 3, 3, 23, 3, 3, 3, 3, 3, 3, 3, 23, 3, 3, 23, 23, 3,
        3, 3, 3, 3, 3, 23, 3, 3, 3, 3, 3, 3, 23, 23, 23, 23, 23, 23, 23,
        3, 23, 3, 3, 3, 23, 23, 23, 23, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 23, 3, 3, 3, 3, 23, 3, 23, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 23, 3, 3, 3, 3, 3, 3, 23, 23, 23, 23, 23, 3, 3, 3, 3, 3, 3,
        3, 23, 3, 3, 3, 3, 3, 3, 3, 3, 23, 23, 23, 23, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
         3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    };

    // const int obstacleTilesLevel1[]  = {};

    // on crée la tilemap avec le niveau précédemment défini
    TileMap map(19,18,684,648,36);
    if (!map.load("tileset_graveyard_tower_interior.png", level)){
        return -1;
	}
	TileMap mapLevel2(19,18,684,648,36);
    if (!mapLevel2.load("tileset_graveyard_tower_interior.png", level2)){
        return -1;
	}

	// for(int j = 0; j < 18; ++j){  
 //        for(int i = 0; i < 19; ++i){
	// 		// std::cout << "x = " << map.get_vertices()[i][j][0].position.x << " , y = " << map.get_vertices()[i][j][0].position.y << std::endl; 
	// 	 	std::cout << level[i + j*map.get_xTiles()] << " ";
 //        }
	//  	std::cout << std::endl;
 //    }


/*creation du personnage du joueur*/
    Character Peter2("sprite.png",0,0,32,32,90,105);
    Peter2.update_index(map);
	std::cout << "x = " << Peter2.m_sprite.getPosition().x << " , y = " << Peter2.m_sprite.getPosition().y << std::endl;

/*creation de giratina*/
    sf::Texture giratinaTexture;
	giratinaTexture.loadFromFile("giratina.png");
	sf::Sprite giratina(giratinaTexture);
	giratina.setTexture(giratinaTexture);
	// giratina.setTextureRect(m_intRect);
	giratina.setPosition(324,105);
	giratina.setScale(2,2);

/*creation de la fumee
    sf::Texture fogTexture;
	fogTexture.loadFromFile("fog.png");
	sf::Sprite fog(fogTexture);

/*creation de la musique
	// sf::Music music;
	// if (!music.openFromFile("pokemon_tower_theme.wav"))
	//     return -1; // erreur
	// music.setVolume(50);
	// music.play();

/*gestion des evenements*/
	sf::Clock clock;
	sf::Event event;
	while (renderWindow.isOpen()){
		while (renderWindow.pollEvent(event)){
			if (event.type == sf::Event::EventType::Closed){
		    	renderWindow.close();
			}
		    Peter2.update_index(map);

		    //evenements lies au deplacement du joueur
		    bool collision = false;
			if (event.type == sf::Event::KeyPressed){
			 	// std::cout << "tile = " << level[Peter2.get_indX() + Peter2.get_indY()*map.get_xTiles()] << std::endl;
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

			if(event.type == sf::Event::KeyReleased){ //sert a remettre le sprite en mode immobile
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

	//mise a jour de l'affichage du jeu
	renderWindow.clear();
	renderWindow.draw(map);
	renderWindow.draw(mapLevel2);	
	renderWindow.draw(giratina);
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