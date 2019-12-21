#pragma once
#include "Player.h"

//Définition Constructeur
Player::Player() : 
	m_intRect(sf::IntRect(64, 0, 32, 32))//initialisation taille d'un rectangle
{
}

//Destructeur
Player::~Player()
{
}

// Dessin du joueur à l'écran si l'image associée à chargé
void Player::Draw(sf::RenderWindow &window)
{
	if(m_loaded) {

		m_sprite.setTextureRect(m_intRect);
		window.draw(m_sprite);

	}
}

// Mouvement du joueur : en bas; en haut, droite et gauche
void Player::Move(Direction direction) {

	if(direction == UP) {

		this -> m_y = m_y - 5; // auto pointeur sur cordonnées du joueur -5 pour descendre
		this -> SetPosition(m_x, m_y);// nouvelle position à partir du changement de coordonnées ci-dessus

		if(this -> m_y < 30) {
			this -> m_y = 30;// pour rester dans les limites du rectangle
		}

	} else if (direction == DOWN) {

		this -> m_y = m_y + 5;// auto pointeur sur cordonnées du joueur +5 pour monter
		this -> SetPosition(m_x, m_y);//// nouvelle position à partir du changement de coordonnées ci-dessus

		if(this -> m_y > SCREENHEIGHT - 30) {
			this -> m_y = SCREENHEIGHT - 30;// pas dépasser la hauteur de l'écran 
		}

	} else if (direction == LEFT) {

		this -> m_x = m_x - 5;
		this -> SetPosition(m_x, m_y);

		if(this -> m_x < 30) {
			this -> m_x = 30;
		}

	} else if (direction == RIGHT) {

		this -> m_x = m_x + 5;
		this -> SetPosition(m_x, m_y);

		if(this -> m_x > SCREENWIDTH - 30) {
			this -> m_x = SCREENWIDTH - 30;// meme principe pour x mais avec la largeur 
		}		

	}

}
