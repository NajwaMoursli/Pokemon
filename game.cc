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


//definition des variables statiques de la classe Game
sf::RenderWindow Game::m_window;
Picture Game::m_introPicture = Picture("intro.png",0,0);
Picture Game::m_gameOverPicture = Picture("game_over.jpg",0,0);
Picture Game::m_battleGiratinaPicture = Picture("combat_vs_giratina.png",0,0);
Picture Game::m_battleEctoplasmaPicture = Picture("combat_vs_ectoplasma.png",0,0);
Picture Game::m_giratina = Picture("giratina.png",324,105,2,2);
Picture Game::m_fogPicture = Picture("fog.png",0,0);
TileMap Game::m_map1 = TileMap(19,18,684,648,36);
TileMap Game::m_map2 = TileMap(19,18,684,648,36);
Character Game::m_peter = Character("sprite.png",0,0,32,32,100,120);
GameState Game::m_gameState = INTRO;
BattleState Game::m_battleState = INTROBATTLE;
sf::Music Game::m_music;
TextPrinted Game::m_textHpPlayer = TextPrinted("Pokemon Platine.ttf", std::to_string(PokemonDragon::DRACOLOSSE.get_hp()), 30, 396, 165);
TextPrinted Game::m_textHpEnemy = TextPrinted("Pokemon Platine.ttf", std::to_string(PokemonGhost::GIRATINA.get_hp()), 30, 124, 40);
TextPrinted Game::m_textAction = TextPrinted("Pokemon Platine.ttf", "Un Giratina sauvage apparait !", 25, 30, 222);



//joue une musique
void Game::music(std::string filename, int volume){
	if(!m_music.openFromFile(filename))
	    return; // erreur
	m_music.setVolume(volume);
	m_music.play();
}


//mise a jour de l'affichage de la map du jeu
void Game::draw_map(){
	m_window.clear();
	m_window.draw(m_map1);
	m_window.draw(m_map2);	
	if(!PokemonGhost::GIRATINA.is_ko()){m_window.draw(m_giratina.get_sprite());}
	m_window.draw(m_peter.get_sprite());
	m_window.draw(m_fogPicture.get_sprite());
	m_window.display();
}


//affiche l'intro du jeu
void Game::draw_intro(){
	m_window.clear();
	m_window.draw(m_introPicture.get_sprite());
	m_window.display();
}


//affiche l'image du combat contre Giratina
void Game::draw_battleGiratina(){
	m_window.clear();
	m_window.draw(m_battleGiratinaPicture.get_sprite());	
	if(m_battleState != CHOICE and m_battleState != APPLYENEMYATTACK1 and m_battleState != APPLYATTACK1){m_window.draw(m_textAction.getText());}
	m_window.draw(m_textHpPlayer.getText());
	m_window.draw(m_textHpEnemy.getText());
	m_window.display();
}


//affiche le game over
void Game::draw_gameOver(){
	m_window.clear();
	m_window.draw(m_gameOverPicture.get_sprite());
	m_window.display();	
}


//lance la boucle qui fait fonctionner le jeu
void Game::launch(){
	m_fogPicture.setColorTransparent();
	m_window.create(sf::VideoMode(800, 440), "Introduction");
	if(!m_map1.load("tileset_graveyard_tower_interior.png", TileMap::get_grid1())){
        return;
	}
    if (!m_map2.load("tileset_graveyard_tower_interior.png", TileMap::get_grid2())){
        return;
	}
    m_peter.update_index(m_map1);
	while(m_gameState != EXIT){
		loop();
	}
	m_window.close();
}


//lance l'intro du jeu
void Game::show_intro(){
	music("prologue partie 1.wav", 20);
	sf::Event event;
	m_window.create(sf::VideoMode(800,440), "Intro");
	draw_intro();

	while(m_gameState == INTRO and m_window.isOpen()){
		while(m_window.pollEvent(event)){
			if(event.type == sf::Event::EventType::Closed){
				m_gameState = EXIT;
			}
			if(event.type == sf::Event::KeyPressed){
			    if(event.key.code == sf::Keyboard::K){ 
			    	m_gameState = MAP;
			    }
			}
		}
	}
}


//lance la scene game over du jeu
void Game::show_gameOver(){
	music("prologue partie 1.wav", 20);
	sf::Event event;
	m_window.create(sf::VideoMode(852,480), "Game Over");
	draw_gameOver();
	while(m_gameState == GAMEOVER and m_window.isOpen()){
		while(m_window.pollEvent(event)){
			if(event.type == sf::Event::EventType::Closed){
				m_gameState = EXIT;
			}
		}
	}
}


//lance la map du jeu
void Game::show_map(){
	m_window.create(sf::VideoMode(304*2.25, 288*2.25), "Tour Pokemon de Lavanville");
	music("distortion-world-pokemon-platinum.wav", 5);
	sf::Clock clock;
	sf::Event event;
    bool collision = false;
	while(m_gameState == MAP and m_window.isOpen()){
		while(m_window.pollEvent(event)){
			if(event.type == sf::Event::EventType::Closed){
		    	m_gameState = EXIT;
			}
		    m_peter.update_index(m_map1);
		    if(!PokemonGhost::GIRATINA.is_ko()) //si le joueur rencontre Giratina
			    if(324 <= m_peter.get_sprite().getPosition().x and m_peter.get_sprite().getPosition().x <= 350 and 196 <= m_peter.get_sprite().getPosition().y
			    	and m_peter.get_sprite().getPosition().y <= 209){
			    	m_gameState = BATTLEGIRATINA;
			    }
		    collision = false;
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
	srand(time(0)); 
	sf::Event event;
	int attackChoice = 5; //une valeur au hasard differente de celles de moves (qui sont 0, 1, 2, 3)
	int enemyAttackChoice = 0;
	BattleState nextBattleState = APPLYATTACK1;
	GameState nextGameState = INTRO;
	std::string str;
	int counter = 0; //var qui quand elle vaut 2 signale que les deux pokemon ont bien attaque
	m_window.create(sf::VideoMode(511, 287), "Battle");
	m_textHpPlayer.setString(std::to_string(PokemonDragon::DRACOLOSSE.get_hp()));
	m_textHpEnemy.setString(std::to_string(PokemonGhost::GIRATINA.get_hp()));
	music("pokemon-platinum-music-giratina-battle-theme.wav", 5);
	while(m_gameState == BATTLEGIRATINA and m_window.isOpen()){
		while(m_window.pollEvent(event)){
			if(event.type == sf::Event::EventType::Closed){
		    	m_gameState = EXIT;}		
			event_introBattle(event);
			event_choice(event, attackChoice);
			event_transition(event, nextBattleState, nextGameState);
			event_lost(event, nextBattleState, nextGameState, str);
			event_won(event, nextBattleState, nextGameState, str);
			event_playerAttack(event, nextBattleState, str, attackChoice, counter);
	    	event_enemyAttack(event, nextBattleState, str, enemyAttackChoice, counter);
		draw_battleGiratina();
		}
	}
}


//teste s'il y a un mouvement
void Game::event_pressKey(sf::Event& event, bool& collision, sf::Clock& clock){
	if(event.key.code == sf::Keyboard::S){ 
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


//teste si c'est le dialogue "Giratina sauvage apparait" qui s'affiche
void Game::event_introBattle(sf::Event& event){
	if(m_battleState == INTROBATTLE){
		if(event.type == sf::Event::KeyPressed){
		    if(event.key.code == sf::Keyboard::K){ 
	    		m_battleGiratinaPicture.setTexture("combat_vs_giratina_moveset.png");
	    		m_battleState = CHOICE;
	    	}	
	    }
	}
}


//teste si c'est au tour du pokemon du joueur d'attaquer
void Game::event_playerAttack(sf::Event& event, BattleState& nextBattleState, std::string& str, int& attackChoice, int& counter){
	if(m_battleState == APPLYATTACK1){
		str = PokemonDragon::DRACOLOSSE.get_name() + " utilise " + PokemonDragon::DRACOLOSSE.get_moves()[attackChoice]->get_name() + ".\n";
		m_textAction.setString(str);
		nextBattleState = APPLYATTACK2;
		m_battleState = TRANSITION;}
	if(m_battleState == APPLYATTACK2){
		if(event.type == sf::Event::KeyPressed){
		    if(event.key.code == sf::Keyboard::K){	
				str = PokemonDragon::DRACOLOSSE.get_moves()[attackChoice]->apply_move(PokemonDragon::DRACOLOSSE,PokemonGhost::GIRATINA);
				m_textHpEnemy.setString(std::to_string(PokemonGhost::GIRATINA.get_hp()));
				m_textAction.setString(str);
				++counter;
				nextBattleState = APPLYATTACK3;	
				m_battleState = TRANSITION;}}}
	if(m_battleState == APPLYATTACK3){
		if(event.type == sf::Event::KeyPressed){
		    if(event.key.code == sf::Keyboard::K){
	    		if(PokemonDragon::DRACOLOSSE.is_ko()){m_battleState = LOST;}	    		
	    		else if(PokemonGhost::GIRATINA.is_ko()){m_battleState = WON;}
				else if(counter == 1){m_battleState = APPLYENEMYATTACK1;} //joueur attaque en premier
				else{counter = 0;  //ennemi attaque en premier					
					m_battleGiratinaPicture.setTexture("combat_vs_giratina_moveset.png"); 
					m_battleState = CHOICE;}}}}
}


//teste si c'est au tour du pokemon ennemi d'attaquer
void Game::event_enemyAttack(sf::Event& event, BattleState& nextBattleState, std::string& str, int& enemyAttackChoice, int& counter){
	if(m_battleState == APPLYENEMYATTACK1){
		enemyAttackChoice = rand() % 4;
		str = PokemonGhost::GIRATINA.get_name() + " utilise " 
			+ PokemonGhost::GIRATINA.get_moves()[enemyAttackChoice]->get_name() + ".\n";
		m_textAction.setString(str);
		nextBattleState = APPLYENEMYATTACK2;
		m_battleState = TRANSITION;}
	if(m_battleState == APPLYENEMYATTACK2){
		if(event.type == sf::Event::KeyPressed){
		    if(event.key.code == sf::Keyboard::K){					
				str = PokemonGhost::GIRATINA.get_moves()[enemyAttackChoice]->apply_move(PokemonGhost::GIRATINA,PokemonDragon::DRACOLOSSE);
				m_textHpPlayer.setString(std::to_string(PokemonDragon::DRACOLOSSE.get_hp()));
				m_textAction.setString(str);
				++counter;
				nextBattleState = APPLYENEMYATTACK3;
				m_battleState = TRANSITION;}}}
	if(m_battleState == APPLYENEMYATTACK3){
		if(event.type == sf::Event::KeyPressed){
		    if(event.key.code == sf::Keyboard::K){
	    		if(PokemonDragon::DRACOLOSSE.is_ko()){m_battleState = LOST;}
				else if(PokemonGhost::GIRATINA.is_ko()){m_battleState = WON;}
				else if(counter == 1){m_battleState = APPLYATTACK1;}				
				else{counter = 0; 
					m_battleGiratinaPicture.setTexture("combat_vs_giratina_moveset.png"); 
					m_battleState = CHOICE;}}}}
}


//teste si c'est le moment ou le joueur doit choisir l'attaque que son pokemon va utiliser
void Game::event_choice(sf::Event& event, int& attackChoice){
	if(m_battleState == CHOICE){
		attackChoice = 5;
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
	    	if(PokemonDragon::DRACOLOSSE.get_speed() >= PokemonGhost::GIRATINA.get_speed()){
    			m_battleState = APPLYATTACK1;
	    		m_battleGiratinaPicture.setTexture("combat_vs_giratina.png");
    		}
    		else{
    			m_battleState = APPLYENEMYATTACK1;
	    		m_battleGiratinaPicture.setTexture("combat_vs_giratina.png");
			}
		}
	}
}


//facilite la transition entre deux etats du combat
void Game::event_transition(sf::Event& event, BattleState& nextBattleState, GameState& nextGameState){
	if(m_battleState == TRANSITION){
		if(event.type == sf::Event::KeyPressed){
		    if(event.key.code == sf::Keyboard::K){ //le point (0,0) est en haut a gauche
	    		m_battleState = nextBattleState;
	    		if(nextGameState == GAMEOVER){
	    			m_battleState = GOTOGAMEOVER;
	    		}
	    		if(nextGameState == MAP){
	    			m_battleState = RETURNTOMAP;
	    		}
	    	}	
	    }
	}
}


//teste si le joueur a gagne
void Game::event_won(sf::Event& event, BattleState& nextBattleState, GameState& nextGameState, std::string& str){
	if(m_battleState == WON){
		if(event.type == sf::Event::KeyPressed){
		    if(event.key.code == sf::Keyboard::K){
				str = "Giratina est KO. Vous avez gagne !";
				m_textAction.setString(str);
				m_battleState = TRANSITION;
				nextBattleState = RETURNTOMAP;
			}
		}
	}
	if(m_battleState == RETURNTOMAP){
		if(event.type == sf::Event::KeyPressed){
		    if(event.key.code == sf::Keyboard::K){
				m_gameState = MAP;
			}
		}
	}
}


//teste si le joueur a perdu
void Game::event_lost(sf::Event& event, BattleState& nextBattleState, GameState& nextGameState, std::string& str){
	if(m_battleState == LOST){
		if(event.type == sf::Event::KeyPressed){
		    if(event.key.code == sf::Keyboard::K){
				str = "Dracolosse est KO. Vous avez perdu !";
				m_textAction.setString(str);
				m_battleState = TRANSITION;
				nextBattleState = GOTOGAMEOVER;
			}
		}
	}
	if(m_battleState == GOTOGAMEOVER){
		if(event.type == sf::Event::KeyPressed){
		    if(event.key.code == sf::Keyboard::K){	
				m_gameState = GAMEOVER;
			}
		}
	}
}


//lance la bonne etape du jeu en fonction de la ou le joueur est (dans la map ? en plein combat ? etc)
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
		case GAMEOVER:
			show_gameOver();
			break;
		default:
			break;
	}
}