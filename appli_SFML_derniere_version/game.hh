#ifndef DEF_GAME
#define DEF_GAME
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "global2.hh"
#include "character.hh"
#include "tilemap.hh"
#include "picture.hh"
#include "text.hh"
#include "global.hh"
#include "move.hh"
#include "pokemon.hh"

class Tilemap;

class Game{
private:
	static sf::RenderWindow m_window;
	static GameState m_gameState;
	static BattleState m_battleState;
	static Picture m_introPicture;
	static Picture m_battleGiratinaPicture;
	static Picture m_battleEctoplasmaPicture;
	static Character m_peter;
	static Character m_giratina;
	static TileMap m_map1;
	static TileMap m_map2;
	static sf::Music m_music;
	static TextPrinted m_textHpPlayer;
	static TextPrinted m_textHpEnemy;
	static TextPrinted m_textAction;

public:
	static void music(std::string filename, int volume);
	static void draw_intro();
	static void draw_map();
	static void draw_battleGiratina();
	static void event_pressKey(sf::Event& event, bool& collision, sf::Clock& clock);	
	static void event_releaseKey(sf::Event& event, sf::Clock& clock);
	static void initialize();
	static void show_intro();	
	static void show_map();
	static void show_battleGiratina();
	static void show_battleEctoplasma();
	static void loop();
	static void launch();
};



#endif