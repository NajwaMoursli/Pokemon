#ifndef DEF_CHARACTER
#define DEF_CHARACTER
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "global2.hh"
#include "tilemap.hh"


class Character{
private:
	sf::Texture m_texture; //images du perso
	sf::IntRect m_intRect; //image selectionnee dans le sprite (le sprite.png)
	int m_indX; //indice en abscisses de la case de la map dans laquelle se trouve le perso
	int m_indY; //indice en ordonnees de la case de la map dans laquelle se trouve le perso
public:
	sf::Sprite m_sprite;
	Character(std::string filename, unsigned int x_inTileset, unsigned int y_inTileset, unsigned int w, 
		unsigned int h, unsigned int x, unsigned int y):m_intRect(x_inTileset,y_inTileset,w,h){
			m_texture.loadFromFile(filename);
			m_sprite.setTexture(m_texture);
			m_sprite.setTextureRect(m_intRect);
			m_sprite.setPosition(x,y);
			m_sprite.setScale(1.5,1.5); //on agrandit l'image du perso car trop petite
			m_indX = 0;
			m_indY = 0;
	}
	sf::Sprite get_sprite() const{return(m_sprite);}
	sf::IntRect get_intRect() const{return(m_intRect);}
	void update_index(TileMap& carte);
	void update_spriteTextureRect(){m_sprite.setTextureRect(m_intRect);}
	void set_intRect(unsigned int p_left,unsigned int p_top){m_intRect.left = p_left;m_intRect.top = p_top;}
	void move_down(bool collision, sf::Clock& clock);
	void move_up(bool collision, sf::Clock& clock);
	void move_right(bool collision, sf::Clock& clock);
	void move_left(bool collision, sf::Clock& clock);
	bool collision(Direction direction, TileMap& carte, const int* tiles,const int* tiles2);
};



#endif