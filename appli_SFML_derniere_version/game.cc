#include <iostream>
#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include "game.hh"
#include "character.hh"
#include "tilemap.hh"
#include "global2.hh"
#include "picture.hh"




sf::RenderWindow Game::m_window;
Picture Game::m_introPicture = Picture("intro.png",0,0);
Picture Game::m_battleGiratinaPicture = Picture("combat_vs_giratina.png",0,0);
Picture Game::m_battleEctoplasmaPicture = Picture("combat_vs_ectoplasma.png",0,0);
TileMap Game::m_map1 = TileMap(19,18,684,648,36);
TileMap Game::m_map2 = TileMap(19,18,684,648,36);
Character Game::m_giratina = Character("giratina.png",324,105);
Character Game::m_peter = Character("sprite.png",0,0,32,32,350,248);
GameState Game::m_gameState = INTRO;
sf::Music Game::m_music;


void Game::display(Picture picture, int w, int h, std::string title){
	m_window.create(sf::VideoMode(w,h), title);
	m_window.clear();
	m_window.draw(picture.get_sprite());
	m_window.display();
}


void Game::music(std::string filename, int volume){
	if(!m_music.openFromFile(filename))
	    return; // erreur
	m_music.setVolume(volume);
	m_music.play();
}


void Game::event_pressKey(sf::Event& event, bool& collision, sf::Clock& clock){
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


void Game::event_releaseKey(sf::Event& event, sf::Clock& clock){
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
	m_window.create(sf::VideoMode(800, 440), "Introduction");
	if(!m_map1.load("tileset_graveyard_tower_interior.png", TileMap::get_grid1())){
        return;
	}
    if (!m_map2.load("tileset_graveyard_tower_interior.png", TileMap::get_grid2())){
        return;
	}
    m_peter.update_index(m_map1);
	while(m_gameState != EXIT){
		std::cout << "loop\n";
		loop();
	}
	m_window.close();
}

void Game::show_intro(){
	music("prologue partie 1.wav", 20);
	sf::Event event;
	display(m_introPicture, 800, 440, "Intro");

	while(m_gameState == INTRO){
		while(m_window.pollEvent(event)){
			if(event.type == sf::Event::EventType::Closed){
				m_gameState = EXIT;
		    	std::cout << "ferme\n";
			}
			if(event.type == sf::Event::KeyPressed){
			    if(event.key.code == sf::Keyboard::J){ 
			    	std::cout << "change\n";
			    	m_gameState = MAP;
			    }
			}
		}
	}
}

void Game::show_map(){
	m_window.create(sf::VideoMode(304*2.25, 288*2.25), "Tour Pokemon de Lavanville");
	music("distortion-world-pokemon-platinum.wav", 5);
	sf::Clock clock;
	sf::Event event;
	while(m_gameState == MAP){
		while(m_window.pollEvent(event)){
			if(event.type == sf::Event::EventType::Closed){
		    	m_gameState = EXIT;
			}
		    m_peter.update_index(m_map1);

		    //si le joueur rencontre Giratina
		    if(324 <= m_peter.m_sprite.getPosition().x and m_peter.m_sprite.getPosition().x <= 350 and 196 <= m_peter.m_sprite.getPosition().y
		    	and m_peter.m_sprite.getPosition().y <= 209){
		    	std::cout << "x = " << m_peter.m_sprite.getPosition().x << " , y = " << m_peter.m_sprite.getPosition().y << std::endl;
		    	m_gameState = BATTLEGIRATINA;
		    }
		    bool collision = false;
			if (event.type == sf::Event::KeyPressed){
			    event_pressKey(event, collision, clock);
			}
			if(event.type == sf::Event::KeyReleased){ //sert a remettre le sprite en mode immobile
				event_releaseKey(event, clock);
            }
        }
    	draw_map();
    }
}


void Game::show_battleGiratina(){
	sf::Event event;
	display(m_battleGiratinaPicture, 511, 287, "Battle");
	music("pokemon-platinum-music-giratina-battle-theme.wav", 5);
	while(m_gameState == BATTLEGIRATINA){
		while(m_window.pollEvent(event)){
			if(event.type == sf::Event::EventType::Closed){
				m_gameState = EXIT;
		    	std::cout << "ferme\n";
			}
			if(event.type == sf::Event::KeyPressed){
			    if(event.key.code == sf::Keyboard::J){ 
			    	std::cout << "change\n";
			    	m_gameState = MAP;
			    }
			}
		}
	}
}

void Game::show_battleEctoplasma(){
	sf::Event event;
	display(m_battleEctoplasmaPicture, 512, 288, "Battle");
	while(m_gameState == BATTLEECTOPLASMA){
		while(m_window.pollEvent(event)){
			if(event.type == sf::Event::EventType::Closed){
				m_gameState = EXIT;
		    	std::cout << "ferme\n";
			}
			if(event.type == sf::Event::KeyPressed){
			    if(event.key.code == sf::Keyboard::J){ 
			    	std::cout << "change\n";

			    	m_gameState = MAP;
			    }
			}
		}
	}
}


void Game::loop(){
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
