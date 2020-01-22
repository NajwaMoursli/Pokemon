#ifndef DEF_GAME
#define DEF_GAME
#include <iostream>
#include <SFML/Graphics.hpp>
#include "global2.hh"
#include "character.hh"
#include "tilemap.hh"

class Tilemap;

class Game{
private:
	static sf::RenderWindow m_window;
	static GameState m_gameState;
	static sf::Sprite m_introPicture;
	static sf::Sprite m_mapPicture;
	static sf::Sprite m_battleGiratinaPicture;
	static sf::Sprite m_battleEctoplasmaPicture;
	static Character m_peter;
	static Character m_giratina;
	static TileMap m_map1;
	static TileMap m_map2;
public:
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