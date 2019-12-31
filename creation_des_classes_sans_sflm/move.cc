#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "move.hh"
#include "global.hh"
#include "pokemon.hh"


void Move::add_category(MoveCategory mc){
	m_categories.push_back(mc);
}

std::string Move::toString(){
	std::string s = "Name : "+m_name;
	s += "\nType : "+typeNames[m_type];
	std::cout << "size categories = " << m_categories.size() << std::endl;
	for(size_t i = 0;i<m_categories.size();i++){
		s += "\n "+ moveCategoriesNames[m_categories[i]];
	}
	s += "\n";
	return(s);
}

bool Move::is_category(MoveCategory mc){
	bool isCategory = false;
	for(size_t i = 0;i<m_categories.size();i++){
		if(m_categories[i] == mc){
			isCategory = true;
		}
	}
	return(isCategory);
}

std::string ChangeStat::toString(){
	std::string s = this->Move::toString();
	s += "Stat changed : "+statNames[m_statChanged];	
	s += "\nModification : "+m_modif;
	s += "\n\n";
	return(s);
}

void ChangeStat::increase(Pokemon& p){
	if(this->get_statChanged() == Attack){
		int oldAttack = p.get_attack();
		p.set_attack(oldAttack*(1+this->get_coeffChange()));
	}
	else if(this->get_statChanged() == SpecialAttack){
		int oldSpecialAttack = p.get_specialAttack();
		p.set_specialAttack(oldSpecialAttack*(1+this->get_coeffChange()));
	}
	else if(this->get_statChanged() == Defense){
		int oldDefense = p.get_defense();
		p.set_defense(oldDefense*(1+this->get_coeffChange()));
	}
	else if(this->get_statChanged() == SpecialDefense){
		int oldSpecialDefense = p.get_specialDefense();
		p.set_specialDefense(oldSpecialDefense*(1+this->get_coeffChange()));		
	}
	else if(this->get_statChanged() == Speed){
		int oldSpeed = p.get_speed();
		p.set_speed(oldSpeed*(1+this->get_coeffChange()));	
	}
}

void ChangeStat::decrease(Pokemon& p){
	if(this->get_statChanged() == Attack){
		int oldAttack = p.get_attack();
		p.set_attack(oldAttack*(1-this->get_coeffChange()));
	}
	else if(this->get_statChanged() == SpecialAttack){
		int oldSpecialAttack = p.get_specialAttack();
		p.set_specialAttack(oldSpecialAttack*(1-this->get_coeffChange()));
	}
	else if(this->get_statChanged() == Defense){
		int oldDefense = p.get_defense();
		p.set_defense(oldDefense*(1-this->get_coeffChange()));
	}
	else if(this->get_statChanged() == SpecialDefense){
		int oldSpecialDefense = p.get_specialDefense();
		p.set_specialDefense(oldSpecialDefense*(1-this->get_coeffChange()));		
	}
	else if(this->get_statChanged() == Speed){
		int oldSpeed = p.get_speed();
		p.set_speed(oldSpeed*(1-this->get_coeffChange()));	
	}
}


void PhysicalDamage::apply_move(Pokemon& attacker,Pokemon& defender){
	int oldHp = defender.get_hp();
	int newHp;
	int damage;
	int ratio = attacker.get_attack()/defender.get_defense();
	const Type defenderType = defender.get_type();
	std::vector<Type> weaknesses = weaknessesTable.at(defenderType);
	for(size_t i = 0;i<weaknesses.size();i++){//s'il y a une faiblesse
		if(m_type == weaknesses[i]){
			damage = 2*m_damage;			
		}
	}
	if(m_type == defender.get_type()){//s'il y a un bonus STAB
		damage = 1.5*m_damage;
	}
	damage *= ratio;	
	newHp = oldHp-damage;
	defender.set_hp(newHp);
}

void SpecialDamage::apply_move(Pokemon& attacker,Pokemon& defender){
	int oldHp = defender.get_hp();
	int newHp;
	int damage;
	int ratio = attacker.get_specialAttack()/defender.get_specialDefense();
	Type defenderType = defender.get_type();
	std::vector<Type> weaknesses = weaknessesTable.at(defenderType);
	for(size_t i = 0;i<weaknesses.size();i++){
		if(m_type == weaknesses[i]){
			damage = 2*m_damage;			
		}
	}
	if(m_type == defender.get_type()){//s'il y a un bonus STAB
		damage = 1.5*m_damage;
	}
	damage *= ratio;
	newHp = oldHp-damage;
	defender.set_hp(newHp);
}

void ChangeStat::apply_move(Pokemon& attacker,Pokemon& defender){
	if(m_targetIsSelf){
		if(m_modif == "increase"){
			this->increase(attacker);
		}
		else if(m_modif == "decrease"){
			this->decrease(attacker);
		}
	}
	else if(!m_targetIsSelf){
		if(m_modif == "increase"){
			this->increase(defender);
		}
		else if(m_modif == "decrease"){
			this->decrease(defender);
		}
	}
}


void PhysicalDamageAndChangeStat::apply_move(Pokemon& attacker,Pokemon& defender){
	this->ChangeStat::apply_move(attacker,defender);
	this->PhysicalDamage::apply_move(attacker,defender);
}


void SpecialDamageAndChangeStat::apply_move(Pokemon& attacker,Pokemon& defender){
	std::cout << "caca\n";
	this->ChangeStat::apply_move(attacker,defender);
	this->SpecialDamage::apply_move(attacker,defender);
}
