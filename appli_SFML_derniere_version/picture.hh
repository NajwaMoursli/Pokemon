#ifndef DEF_PICTURE		
#define DEF_PICTURE
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>


class Picture{
	protected:
		sf::Sprite m_sprite;
		sf::Texture m_texture;
	public:
		Picture(std::string filename, int x, int y){
			m_texture.loadFromFile(filename);
			m_sprite.setTexture(m_texture);
			m_sprite.setPosition(x,y);
		}

		Picture(std::string filename, int x, int y, int scaleX, int scaleY){
			m_texture.loadFromFile(filename);
			m_sprite.setTexture(m_texture);
			m_sprite.setPosition(x,y);
			m_sprite.setScale(scaleX,scaleY); //on agrandit l'image du perso car trop petite
		}

		void setTexture(std::string filename){
			m_texture.loadFromFile(filename);
			m_sprite.setTexture(m_texture);
		}

		void setColorTransparent(){
			m_sprite.setColor(sf::Color(255, 255, 255, 95));
		}

		sf::Sprite get_sprite() const{return(m_sprite);}
};

#endif