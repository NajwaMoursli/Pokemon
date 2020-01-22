#include <iostream>
#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include "game.hh"
#include "character.hh"
#include "tilemap.hh"
#include "global2.hh"



// sf::RenderWindow Game::window;
// sf::m_window m_window(sf::VideoMode(304*2.25, 288*2.25), "Demo Game");
sf::RenderWindow Game::m_window;
sf::Sprite Game::m_introPicture;
sf::Sprite Game::m_mapPicture;
sf::Sprite Game::m_battleGiratinaPicture;
sf::Sprite Game::m_battleEctoplasmaPicture;
TileMap Game::m_map1 = TileMap(19,18,684,648,36);
TileMap Game::m_map2 = TileMap(19,18,684,648,36);
Character Game::m_giratina = Character("giratina.png",324,105);
Character Game::m_peter = Character("sprite.png",0,0,32,32,90,105);
GameState Game::m_gameState = INTRO;


//mise a jour de l'affichage du jeu
void Game::draw_map(){
	m_window.clear();
	m_window.draw(m_map1);
	m_window.draw(m_map2);	
	m_window.draw(m_giratina.m_sprite);
	m_window.draw(m_peter.m_sprite);
	m_window.display();
	// m_window.draw(fog);
}

void Game::launch(){
	std::cout << "caca\n";
	m_window.create(sf::VideoMode(304*2.25, 288*2.25), "Demo Game");

	if(!m_map1.load("tileset_graveyard_tower_interior.png", TileMap::get_grid1())){
        return;
	}
    if (!m_map2.load("tileset_graveyard_tower_interior.png", TileMap::get_grid2())){
        return;
	}

    m_peter.update_index(m_map1);
    m_giratina.update_index(m_map1);    

	/*creation de la musique*/
	sf::Music music;
	if (!music.openFromFile("pokemon_tower_theme.wav"))
	    return; // erreur
	music.setVolume(38);
	music.play();

	while(m_gameState != EXIT){
		loop();
	}

	m_window.close();
}

void Game::show_intro(){
	sf::Event event;
	m_window.create(sf::VideoMode(800, 440), "Introduction");
	sf::Texture introTexture;
	introTexture.loadFromFile("intro.png");
	m_introPicture.setTexture(introTexture);
	m_introPicture.setPosition(0,0);
	while(m_window.isOpen() and m_gameState == INTRO){
		while(m_window.pollEvent(event)){
			if(event.type == sf::Event::EventType::Closed){
		    	m_window.close();
			}
			if(event.type == sf::Event::KeyPressed){
			    if(event.key.code == sf::Keyboard::J){ 
			    	m_gameState = MAP;
			    }
			}
		}
	}
}

void Game::show_map(){
	draw_map();
	sf::Clock clock;
	sf::Event event;
	while(m_window.isOpen()){
		while(m_window.pollEvent(event)){
			if(event.type == sf::Event::EventType::Closed){
		    	m_window.close();
			}
		    m_peter.update_index(m_map1);

		    //evenements lies au deplacement du joueur
		    bool collision = false;
			if (event.type == sf::Event::KeyPressed){
			    if (event.key.code == sf::Keyboard::S){ 
			    	collision = m_peter.collision(DOWN, m_map1, TileMap::get_grid1(), TileMap::get_grid2());
			    	m_peter.move_down(collision, clock);
			    }
			    if (event.key.code == sf::Keyboard::Z){
			    	collision = m_peter.collision(UP, m_map1, TileMap::get_grid1(), TileMap::get_grid2());
			    	m_peter.move_up(collision, clock);
			    }
			    if (event.key.code == sf::Keyboard::D){
			    	collision = m_peter.collision(RIGHT, m_map1, TileMap::get_grid1(), TileMap::get_grid2());
			    	m_peter.move_right(collision, clock);
			    }
			    if (event.key.code == sf::Keyboard::Q){
			    	collision = m_peter.collision(LEFT, m_map1, TileMap::get_grid1(), TileMap::get_grid2());			    	
			    	m_peter.move_left(collision, clock);
			    }
			}

			if(event.type == sf::Event::KeyReleased){ //sert a remettre le sprite en mode immobile
				if(event.key.code == sf::Keyboard::S){
				 m_peter.set_intRect(67,33);
		 		 m_peter.update_spriteTextureRect();
				 clock.restart();
				}	
				if(event.key.code == sf::Keyboard::Z){
				 m_peter.set_intRect(0,0);
				 m_peter.update_spriteTextureRect();
				 clock.restart();
				}
				if(event.key.code == sf::Keyboard::D){
				 m_peter.set_intRect(35,0);
		 		 m_peter.update_spriteTextureRect();
				 clock.restart();
				}
				if(event.key.code == sf::Keyboard::Q){
				 m_peter.set_intRect(5,65);
				 m_peter.update_spriteTextureRect();
				 clock.restart();
				}
            }
        }
    }
}


void Game::show_battleGiratina(){
	sf::Event event;
	m_window.create(sf::VideoMode(511, 287), "Battle");
	sf::Texture texture;
	texture.loadFromFile("combat_vs_giratina.png");
	m_battleGiratinaPicture.setTexture(texture);
	m_battleGiratinaPicture.setPosition(0,0);
}

void Game::show_battleEctoplasma(){
	sf::Event event;
	m_window.create(sf::VideoMode(512, 288), "Battle");
	sf::Texture texture;
	texture.loadFromFile("combat_vs_ectoplasma.png");
	m_battleEctoplasmaPicture.setTexture(texture);
	m_battleEctoplasmaPicture.setPosition(0,0);
}


void Game::loop(){
	while(m_gameState != EXIT){
		switch(m_gameState){
			case MAP:
				show_map();
				break;
			case INTRO:
				show_intro();
				break;
			case BATTLEGIRATINA:
				show_battleGiratina();
				break;
			case BATTLEECTOPLASMA:
				show_battleEctoplasma();
				break;
			default:
				break;
		}
	}
}
