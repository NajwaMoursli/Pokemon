#include <iostream>
#include <string>
#include <ctime> 
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include "game.hh"
#include "character.hh"
#include "tilemap.hh"
#include "global2.hh"
#include "picture.hh"
#include "text.hh"
#include "global.hh"
#include "move.hh"
#include "pokemon.hh"


sf::RenderWindow Game::m_window;
Picture Game::m_introPicture = Picture("intro.png",0,0);
Picture Game::m_battleGiratinaPicture = Picture("combat_vs_giratina.png",0,0);
Picture Game::m_battleEctoplasmaPicture = Picture("combat_vs_ectoplasma.png",0,0);
TileMap Game::m_map1 = TileMap(19,18,684,648,36);
TileMap Game::m_map2 = TileMap(19,18,684,648,36);
Character Game::m_giratina = Character("giratina.png",324,105);
Character Game::m_peter = Character("sprite.png",0,0,32,32,350,248);
GameState Game::m_gameState = INTRO;
BattleState Game::m_battleState = INTROBATTLE;
sf::Music Game::m_music;
TextPrinted Game::m_textHpPlayer = TextPrinted("Pokemon Platine.ttf", "a", 30, 396, 165);
TextPrinted Game::m_textHpEnemy = TextPrinted("Pokemon Platine.ttf", "a", 30, 124, 40);
TextPrinted Game::m_textAction = TextPrinted("Pokemon Platine.ttf", "Un Giratina sauvage apparait !", 30, 30, 222);


void Game::draw_battleGiratina(){
	m_window.clear();
	m_window.draw(m_battleGiratinaPicture.get_sprite());	
	if(m_battleState != CHOICE and m_battleState != APPLYENEMYATTACK1 and m_battleState != APPLYATTACK1){m_window.draw(m_textAction.getText());}
	m_window.draw(m_textHpPlayer.getText());
	m_window.draw(m_textHpEnemy.getText());
	// std::cout << "text prout\n";
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

void Game::draw_intro(){
	m_window.clear();
	m_window.draw(m_introPicture.get_sprite());
	m_window.display();
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
	m_window.create(sf::VideoMode(800,440), "Intro");
	draw_intro();

	while(m_gameState == INTRO){
		while(m_window.pollEvent(event)){
			if(event.type == sf::Event::EventType::Closed){
				m_gameState = EXIT;
		    	std::cout << "ferme\n";
			}
			if(event.type == sf::Event::KeyPressed){
			    if(event.key.code == sf::Keyboard::K){ 
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
	std::cout << "pipicaca\n";
	srand(time(0)); 
	sf::Event event;
	int attackChoice = 5; //une valeur au hasard differente de celles de moves (qui sont 0, 1, 2, 3)
	std::string str;
	bool playerAttackFirst = true;
	int counter = 0; //var qui quand elle vaut 2 signale que les deux pokemon ont bien attaque
	m_window.create(sf::VideoMode(511, 287), "Battle");
	// draw_battleGiratina()
	music("pokemon-platinum-music-giratina-battle-theme.wav", 5);
	while(m_gameState == BATTLEGIRATINA){
		while(m_window.pollEvent(event)){
			if(event.type == sf::Event::EventType::Closed){
		    	m_window.close();
			}		
	    	if(m_battleState == INTROBATTLE){
	    		std::cout << "IN introbattle\n";
	    		if(event.type == sf::Event::KeyPressed){
				    if(event.key.code == sf::Keyboard::K){ //le point (0,0) est en haut a gauche
			    		m_battleGiratinaPicture.setTexture("combat_vs_giratina_moveset.png");
			    		m_battleState = CHOICE;
			    	}	
			    }
			}
	    	if(m_battleState == CHOICE){
	    		std::cout << "IN choice\n";
	    		if(event.type == sf::Event::KeyPressed){
		    		if(event.key.code == sf::Keyboard::Numpad1){ //le point (0,0) est en haut a gauche
			    		attackChoice = 0;    		
			    	}
			    	if(event.key.code == sf::Keyboard::Numpad2){ //le point (0,0) est en haut a gauche
						attackChoice = 1;				    		
			    	}
			    	if(event.key.code == sf::Keyboard::Numpad3){ //le point (0,0) est en haut a gauche
						attackChoice = 2;			    		
			    	}
			    	if(event.key.code == sf::Keyboard::Numpad4){ //le point (0,0) est en haut a gauche
						attackChoice = 3;			    	
			    	}
		    	}
		    	if(attackChoice != 5){
		    		std::cout << "IN END CHOICE\n";
			    	if(PokemonDragon::DRACOLOSSE.get_speed() >= PokemonGhost::GIRATINA.get_speed()){
			    			playerAttackFirst = true;
			    			m_battleState = APPLYATTACK1;
			    		}
		    		else{
		    			playerAttackFirst = false;
		    			m_battleState = APPLYENEMYATTACK1;
	    			}
	    		}
	    		std::cout << "cacaprout\n";	
	    	}
			if(m_battleState == APPLYATTACK1){
	    		std::cout << "IN APPLYATTACK1\n";
				str = PokemonDragon::DRACOLOSSE.get_name() + " utilise " 
					+ PokemonDragon::DRACOLOSSE.get_moves()[attackChoice]->get_name() + ".\n";
				m_textAction.setString(str);
				m_battleState = APPLYATTACK2;
	    		m_battleGiratinaPicture.setTexture("combat_vs_giratina.png");				
			}
			if(m_battleState == APPLYATTACK2){
	    		std::cout << "IN APPLYATTACK2\n";
				if(event.type == sf::Event::KeyPressed){
				    if(event.key.code == sf::Keyboard::K){
						str = PokemonDragon::DRACOLOSSE.get_moves()[attackChoice]->apply_move(PokemonDragon::DRACOLOSSE,PokemonGhost::GIRATINA);
						m_textHpEnemy.setString(std::to_string(PokemonGhost::GIRATINA.get_hp()));
						m_textAction.setString(str);
						if(playerAttackFirst){m_battleState = APPLYENEMYATTACK1;}
						else if(PokemonGhost::GIRATINA.is_ko()){m_battleState = WON;}
						else{m_battleState = CHOICE;}
					}
				}
			}
			if(m_battleState == APPLYENEMYATTACK1){
	    		std::cout << "IN APPLYENEMYATTACK1\n";			
				int enemyAttackChoice = rand() % 3;
				str = PokemonGhost::GIRATINA.get_name() + " utilise " 
					+ PokemonGhost::GIRATINA.get_moves()[enemyAttackChoice]->get_name() + ".\n";
				m_textAction.setString(str);
				m_battleState = APPLYENEMYATTACK2;
	    		m_battleGiratinaPicture.setTexture("combat_vs_giratina.png");
			}
			if(m_battleState == APPLYENEMYATTACK2){
	    		std::cout << "IN APPLYENEMYATTACK2\n";			
				if(event.type == sf::Event::KeyPressed){
				    if(event.key.code == sf::Keyboard::K){
						str = PokemonGhost::GIRATINA.get_moves()[attackChoice]->apply_move(PokemonGhost::GIRATINA,PokemonDragon::DRACOLOSSE);
						m_textHpPlayer.setString(std::to_string(PokemonDragon::DRACOLOSSE.get_hp()));
						m_textAction.setString(str);
						if(!playerAttackFirst){m_battleState = APPLYATTACK1;}
						else if(PokemonDragon::DRACOLOSSE.is_ko()){m_battleState = LOST;}
						else{m_battleState = CHOICE;}
					}
				}
			}
			if(m_battleState == LOST){
				if(event.type == sf::Event::KeyPressed){
				    if(event.key.code == sf::Keyboard::K){
						str = "Dracolosse est KO. Vous avez perdu !";
						m_textAction.setString(str);
						m_battleState = RETURNTOMAP;
					}
				}
			}
			if(m_battleState == WON){
				if(event.type == sf::Event::KeyPressed){
				    if(event.key.code == sf::Keyboard::K){
						str = "Giratina est KO. Vous avez gagne !";
						m_textAction.setString(str);
						m_battleState = RETURNTOMAP;
					}
				}
			}
			if(m_battleState == RETURNTOMAP){
				m_gameState = MAP;
			}
	   }
	   draw_battleGiratina();
	}
}

void Game::show_battleEctoplasma(){
	sf::Event event;
	//draw_battleEctoplasma;
	while(m_gameState == BATTLEECTOPLASMA){
		while(m_window.pollEvent(event)){
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
