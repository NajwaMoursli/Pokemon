#pragma once
#include "DisplayedObject.h"
//Définition du constructeur par défaut de la classe DisplayedObject
DisplayedObject::DisplayedObject()
	: m_loaded(true)
{

}

//Définition du Destructeur
DisplayedObject::~DisplayedObject()
{
}

// Chargement de l'objet à affiché si un nom de fichier valide est donné 
void DisplayedObject::Load(std::string filename)
{
	if(m_texture.loadFromFile(filename) == false)
	{
		m_loaded = false;
	}
	else
	{
		m_sprite.setTexture(m_texture);
		m_filename = filename;
		m_loaded = true;
	}
}


void DisplayedObject::Draw(sf::RenderWindow &window)
{
	if(m_loaded)
	{
		window.draw(m_sprite);
	}
}


void DisplayedObject::SetPosition(float x, float y)
{
	if(m_loaded)
	{
		m_x = x;
		m_y = y;
		m_sprite.setPosition(x ,y);
	}
}
