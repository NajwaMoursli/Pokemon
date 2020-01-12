#ifndef DEF_CHARACTER
#define DEF_CHARACTER
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>


class Character{
private:
	sf::Texture m_texture;
	sf::IntRect m_intRect;
public:
	sf::Sprite m_sprite;
	Character(std::string filename, unsigned int x_inTileset, unsigned int y_inTileset, unsigned int w, 
		unsigned int h, unsigned int x, unsigned int y):m_intRect(x_inTileset,y_inTileset,w,h){
			m_texture.loadFromFile(filename);
			m_sprite.setTexture(m_texture);
			m_sprite.setTextureRect(m_intRect);
			m_sprite.setPosition(x,y);
			m_sprite.setScale(1.5,1.5);
			std::cout << "caca\n";
	}
	sf::Sprite get_sprite() const{return(m_sprite);}
	sf::IntRect get_intRect() const{return(m_intRect);}
	void update_spriteTextureRect(){m_sprite.setTextureRect(m_intRect);}
	void set_intRect(unsigned int p_left,unsigned int p_top){m_intRect.left = p_left;m_intRect.top = p_top;std::cout << "pipi\n";}
	void immobile_down(sf::Clock& clock){m_intRect.left = 0;m_intRect.top = 0;}
	void move_down(sf::Clock& clock);
	void move_up(sf::Clock& clock);
	void move_right(sf::Clock& clock);
	void move_left(sf::Clock& clock);
};



#endif