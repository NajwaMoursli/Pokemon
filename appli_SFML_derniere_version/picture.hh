#ifndef DEF_PICTURE		
#define DEF_PICTURE
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>


class Picture{
	private:
		sf::Sprite m_sprite;
		sf::Texture m_texture;
	public:
		Picture(std::string filename, int x, int y){
			m_texture.loadFromFile(filename);
			m_sprite.setTexture(m_texture);
			m_sprite.setPosition(x,y);
		}

		void setTexture(std::string filename){
			m_texture.loadFromFile(filename);
			m_sprite.setTexture(m_texture);
		}

		sf::Sprite get_sprite() const{return(m_sprite);}
};

#endif