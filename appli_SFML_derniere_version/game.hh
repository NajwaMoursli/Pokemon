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

class Tilemap;

class Game{
private:
	static sf::RenderWindow m_window;
	static GameState m_gameState;
	static Picture m_introPicture;
	static Picture m_battleGiratinaPicture;
	static Picture m_battleEctoplasmaPicture;
	static Character m_peter;
	static Character m_giratina;
	static TileMap m_map1;
	static TileMap m_map2;
	static sf::Music m_music;
public:
	static void music(std::string filename, int volume);
	static void display(Picture picture, int w, int h, std::string title);
	static void event_pressKey(sf::Event& event, bool& collision, sf::Clock& clock);	
	static void event_releaseKey(sf::Event& event, sf::Clock& clock);
	static void draw_map();
	static void initialize();
	static void show_intro();	
	static void show_map();
	static void show_battleGiratina();
	static void show_battleEctoplasma();
	static void loop();
	static void launch();
};



#endif