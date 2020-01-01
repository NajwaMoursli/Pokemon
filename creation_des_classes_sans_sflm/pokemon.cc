#include "pokemon.hh"
#include "global.hh"
#include "move.hh"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


std::string Pokemon::toString(){
	// std::cout << m_name << std::endl;
	std::string s = "Name : "+m_name;
	s += "\nType : " + typeNames[m_type]; //car par defaut m_type part de zero
	s += "\nHp : " + std::to_string(m_hp);	
	s += "\nAttack : " + std::to_string(m_attack);
	s += "\nSpecial attack : " + std::to_string(m_specialAttack);
	s += "\nDefense : " + std::to_string(m_defense);
	s += "\nSpecial defense : " + std::to_string(m_specialDefense);
	s += "\nSpeed : " + std::to_string(m_speed);
	s += "\nMoveset : ";
	s += "\n  " + m_moves[0]->get_name();
	s += "\n  " + m_moves[1]->get_name();
	s += "\n  " + m_moves[2]->get_name();
	s += "\n  " + m_moves[3]->get_name();
	s += "\n\n";
	return(s);
}

std::string Pokemon::movesetToString(){
	std::string s = "Moveset : "+m_name;
	s += "\n  1. " + m_moves[0]->get_name();
	s += "\n  2. " + m_moves[1]->get_name();
	s += "\n  3. " + m_moves[2]->get_name();
	s += "\n  4. " + m_moves[3]->get_name();
	s += "\n\n";
	return(s);
}