#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "character.hh"
#include "tilemap.hh"


void Character::move_down(sf::Clock& clock){
	if(clock.getElapsedTime().asSeconds() > 0.13){ //pour ralentir l'animation, sinon elle est trop rapide
		// std::cout << m_intRect.left << ", " << m_intRect.top << std::endl; //immobile bas : 67 33
		if((m_intRect.left == 67 and m_intRect.top == 33)or(m_intRect.left == 68 and m_intRect.top == 97)){
	    	m_intRect.left = 66;
			m_intRect.top = 64;
		}
		else if(m_intRect.left == 66 and m_intRect.top == 64){
			m_intRect.left = 68;
			m_intRect.top = 97;
		}
		else{ //si le m_sprite dans le mauvais sens, on le remet dans le bon sens : le sens du deplacement
			m_intRect.left = 67;
			m_intRect.top = 33;
		}
	m_sprite.setTextureRect(m_intRect);
	m_sprite.move(0,14);
	clock.restart();
	}
}

void Character::move_up(sf::Clock& clock){
	if(clock.getElapsedTime().asSeconds() > 0.13){ //pour ralentir l'animation, sinon elle est trop rapide
		// std::cout << m_intRect.left << ", " << m_intRect.top << std::endl;
		if((m_intRect.left == 0 and m_intRect.top == 0)or(m_intRect.left == 69 and m_intRect.top == 0)){
	    	m_intRect.left = 36;
			m_intRect.top = 96;
		}
		else if(m_intRect.left == 36 and m_intRect.top == 96){
			m_intRect.left = 69;
			m_intRect.top = 0;
		}
		else{
			m_intRect.left = 0;
			m_intRect.top = 0;
			// std::cout << "changement immobile dans move up\n";
		}
	m_sprite.setTextureRect(m_intRect);
	m_sprite.move(0,-14);
	clock.restart();
	}
}

 //bas : 67 33 //haut : 0 0 //right : 35 0 //left 5 65
void Character::move_right(sf::Clock& clock){
	if(clock.getElapsedTime().asSeconds() > 0.13){ //pour ralentir l'animation, sinon elle est trop rapide
		// std::cout << m_intRect.left << ", " << m_intRect.top << std::endl;
		if((m_intRect.left == 35 and m_intRect.top == 0)or(m_intRect.left == 35 and m_intRect.top == 65)){
	    	m_intRect.left = 34;
			m_intRect.top = 33;
		}
		else if(m_intRect.left == 34 and m_intRect.top == 33){
			m_intRect.left = 35;
			m_intRect.top = 65;
		}
		else{
			m_intRect.left = 35;
			m_intRect.top = 0;
		}
	m_sprite.setTextureRect(m_intRect);
	m_sprite.move(14,0);
	clock.restart();
	}
}

 //bas : 67 33 //haut : 0 0 //right : 35 0 //left 5 65
void Character::move_left(sf::Clock& clock){
	if(clock.getElapsedTime().asSeconds() > 0.13){ //pour ralentir l'animation, sinon elle est trop rapide
		// std::cout << m_intRect.left << ", " << m_intRect.top << std::endl;
		if((m_intRect.left == 5 and m_intRect.top == 65)or(m_intRect.left == 4 and m_intRect.top == 96)){
	    	m_intRect.left = 4;
			m_intRect.top = 34;
		}
		else if(m_intRect.left == 4 and m_intRect.top == 34){
			m_intRect.left = 4;
			m_intRect.top = 96;
		}
		else{
			m_intRect.left = 5;
			m_intRect.top = 65;
		}
	m_sprite.setTextureRect(m_intRect);
	m_sprite.move(-14,0);
	clock.restart();
	}
}

//donne l'indice du tile dans lequel se trouve un point :
// - int width : largeur 
// void Character::update_index(TileMap carte){
// 	m_indX = m_sprite.getPosition().x/carte.get_tileSize();
// 	m_indY = m_sprite.getPosition().y/carte.get_tileSize();
// 	std::cout << "indx = " << m_indX << ", indy = " << m_indY << std::endl;
// }

bool collision(TileMap map){
	bool collision = false;

	return(collision);
}