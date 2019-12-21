#ifndef DEF_POKEMON
#define DEF_POKEMON
#include <iostream>
#include <string>
#include "type_enumerate.hh"

class Pokemon{
protected:
	std::string m_name;
	Type m_type;
	int m_hp; //points de vie
	int m_attack;
	int m_specialAttack;
	int m_defense;
	int m_specialDefense;
	int m_speed;
public:
	//constructeur par liste d'initialisation qui initialise tous les attributs d'une instance de Pokemon
	Pokemon(std::string p_name,Type p_type,int p_hp,int p_attack,int p_specialAttack,int p_defense,
		int p_specialDefense,int p_speed):
		m_name(p_name),m_type(p_type),m_hp(p_hp),m_attack(p_attack),m_specialAttack(p_specialAttack),
		m_defense(p_defense),m_specialDefense(p_specialDefense),m_speed(p_speed){}
	std::string get_name() const{return(m_name);}
	Type get_type() const{return(m_type);}
	int get_hp() const{return(m_hp);}
	int get_attack() const{return(m_attack);}
	int get_specialAttack() const{return(m_specialAttack);}
	int get_defense() const{return(m_defense);}
	int get_specialDefense() const{return(m_specialDefense);}
	int get_speed() const{return(m_speed);}
	std::string toString(); //retourne une string qui decrit un pokemon
	virtual void receive_dommage(const Pokemon& p) = 0;//applique les dommages recues par un pokemon, version non definitive !
													   //virtuelle car chaque Pokemon recoit des degats differents en fonction
													   //de son type et donc de ses faiblesses et de ses avantages
};


#endif