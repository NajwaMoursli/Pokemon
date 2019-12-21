#include "pokemon.hh"
#include <iostream>
#include <string>
#include <vector>


std::string Pokemon::toString(){
	std::string s = "Name : "+m_name;
	s += "\nType : " + typeNames[m_type];
	s += "\nAttack : " + std::to_string(m_attack);
	s += "\nSpecial attack : " + std::to_string(m_specialAttack);
	s += "\nDefense : " + std::to_string(m_defense);
	s += "\nSpecial defense : " + std::to_string(m_specialDefense);
	s += "\nSpeed : " + std::to_string(m_speed);
	return(s);
}
