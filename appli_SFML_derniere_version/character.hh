#ifndef DEF_CHARACTER
#define DEF_CHARACTER
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "global2.hh"
#include "tilemap.hh"



class Character{
private:
	sf::Texture m_texture; //images du perso
	sf::IntRect m_intRect; //image selectionnee dans le sprite (le sprite.png)
	std::vector<sf::Vector2<int>> m_ind;
public:
	sf::Sprite m_sprite;

	//constructeur pour le perso du joueur
	Character(std::string filename, unsigned int x_inTileset, unsigned int y_inTileset, unsigned int w, 
		unsigned int h, unsigned int x, unsigned int y):m_intRect(x_inTileset,y_inTileset,w,h){
			m_texture.loadFromFile(filename);
			m_sprite.setTexture(m_texture);
			m_sprite.setTextureRect(m_intRect);
			m_sprite.setPosition(x,y);
			m_sprite.setScale(1.5,1.5); //on agrandit l'image du perso car trop petite
			m_ind = {{0,0},{0,0},{0,0},{0,0}};
	}

	//constructeur pour les autres perso du jeu (les mob)
	Character(std::string filename, unsigned int x, unsigned int y){
			m_texture.loadFromFile(filename);
			m_sprite.setTexture(m_texture);
			m_sprite.setPosition(x,y);
			m_sprite.setScale(2,2); //on agrandit l'image du perso car trop petite
			// giratina.setPosition(324,105);
	}

	sf::Sprite get_sprite() const{return(m_sprite);}
	sf::IntRect get_intRect() const{return(m_intRect);}
	std::vector<sf::Vector2<int>> get_ind() const{return(m_ind);}
	std::vector<sf::Vector2<int>> get_indEdges(const TileMap& carte, int x, int y);
	bool inObstacleTile(const TileMap& carte, const int* tiles,const int* tiles2, std::vector<sf::Vector2<int>> indEdges, int& intersectX, int& intersectY);
	void update_index(const TileMap& carte);
	void update_spriteTextureRect(){m_sprite.setTextureRect(m_intRect);}
	void set_intRect(unsigned int p_left,unsigned int p_top){m_intRect.left = p_left;m_intRect.top = p_top;}
	void move_down(bool collision, sf::Clock& clock);
	void move_up(bool collision, sf::Clock& clock);
	void move_right(bool collision, sf::Clock& clock);
	void move_left(bool collision, sf::Clock& clock);
	bool collision(Direction direction, const TileMap& carte, const int* tiles,const int* tiles2);
};



#endif