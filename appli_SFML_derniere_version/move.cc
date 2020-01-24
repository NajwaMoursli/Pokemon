#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "move.hh"
#include "global.hh"
#include "pokemon.hh"


const SpecialDamageAndChangeStat SpecialDamageAndChangeStat::BALLOMBRE = 
	SpecialDamageAndChangeStat("Ball'Ombre",Ghost,80,SpecialDefense,"decrease",0.25);
const SpecialDamageAndChangeStat SpecialDamageAndChangeStat::EXPLOFORCE = 
	SpecialDamageAndChangeStat("Exploforce",Fight,120,SpecialDefense,"decrease",0.25);
const SpecialDamage SpecialDamage::TONNERRE = 
	SpecialDamage("Tonnerre",Electric,90);
const SpecialDamage SpecialDamage::PUISSANCECACHEEFEU = 
	SpecialDamage("Puissance Cachee Feu",Fire,60);

const PhysicalDamage PhysicalDamage::POINGFEU = PhysicalDamage("Poing Feu",Fire,75);
const PhysicalDamage PhysicalDamage::DRACOGRIFFE = PhysicalDamage("Draco-Griffe",Fire,80);
const PhysicalDamage PhysicalDamage::HYDROQUEUE = PhysicalDamage("Hydro-Queue",Fire,90);
const ChangeStat ChangeStat::DANSEDRACO = ChangeStat("Danse Draco",Dragon,Attack,"increase",true);

const SpecialDamage SpecialDamage::POUVANTIQUE = SpecialDamage("Pouv. Antique",Rock,60);
const PhysicalDamage PhysicalDamage::REVENANT = PhysicalDamage("Revenant",Ghost,120);
const PhysicalDamage PhysicalDamage::TRANCHE = PhysicalDamage("Tranche",Normal,70);


//Marche aussi (version avec pointeurs)
// const SpecialDamageAndChangeStat* SpecialDamageAndChangeStat::BALLOMBRE = 
// 	new SpecialDamageAndChangeStat("Ball'Ombre",Ghost,80,SpecialDefense,"decrease",0.25);



void Move::add_category(MoveCategory mc){
	m_categories.push_back(mc);
}

std::string Move::toString() const{
	std::string s = "Name : "+m_name;
	s += "\nType : "+typeNames[m_type];
	// std::cout << "size categories = " << m_categories.size() << std::endl;
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

std::string ChangeStat::toString() const{
	std::string s = this->Move::toString();
	s += "Stat changed : "+statNames[m_statChanged];	
	s += "\nModification : "+m_modif;
	s += "\n\n";
	return(s);
}

void ChangeStat::increase(Pokemon& p) const{
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

void ChangeStat::decrease(Pokemon& p) const{
	std::cout << "stat changed = " << statNames[this->get_statChanged()] << std::endl;
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
		std::cout << "get_coeffChange = " << this->get_coeffChange() << std::endl;
		std::cout << "mult = " << 1-this->get_coeffChange() << std::endl;
		std::cout << oldSpecialDefense*(1-this->get_coeffChange()) << std::endl;
		p.set_specialDefense(oldSpecialDefense*(1-this->get_coeffChange()));		
	}
	else if(this->get_statChanged() == Speed){
		int oldSpeed = p.get_speed();
		p.set_speed(oldSpeed*(1-this->get_coeffChange()));	
	}
}


void PhysicalDamage::apply_move(Pokemon& attacker,Pokemon& defender) const{
	int oldHp = defender.get_hp();
	int newHp;
	int damage = m_damage;
	int ratio = attacker.get_attack()/defender.get_defense();
	const Type defenderType = defender.get_type();
	std::vector<Type> weaknesses = weaknessesTable.at(defenderType);
	if(m_type == attacker.get_type()){//s'il y a un bonus STAB
		damage *= 1.5;
	}
	for(size_t i = 0;i<weaknesses.size();i++){//s'il y a une faiblesse
		if(m_type == weaknesses[i]){
			damage *= 2;			
		}
	}
	damage *= ratio;
	std::cout << attacker.get_name() + " a perdu " + std::to_string(damage) + " pv.\n";		
	newHp = oldHp-damage;
	if(newHp < 0){defender.set_hp(0);}
	else{defender.set_hp(newHp);}
}

void SpecialDamage::apply_move(Pokemon& attacker,Pokemon& defender) const{
	std::cout << "apply_move Special\n";
	int oldHp = defender.get_hp();
	int newHp;
	int damage = m_damage;
	float ratio = attacker.get_specialAttack()/defender.get_specialDefense();
	Type defenderType = defender.get_type();
	std::vector<Type> weaknesses = weaknessesTable.at(defenderType);
	if(m_type == attacker.get_type()){//s'il y a un bonus STAB
		damage *= 1.5;
	}
	for(size_t i = 0;i<weaknesses.size();i++){
		if(m_type == weaknesses[i]){
			damage *= 2;	
			std::cout << m_damage << std::endl;
		}
	}
	damage *= ratio;
	std::cout << "puissance de l'attaque = " << m_damage << std::endl;

	std::cout << "ratio = " << ratio << std::endl;
	std::cout << attacker.get_name() + " a perdu " + std::to_string(damage) + " pv.\n";
	newHp = oldHp-damage;
	if(newHp < 0){defender.set_hp(0);}
	else{defender.set_hp(newHp);}
}

void ChangeStat::apply_move(Pokemon& attacker,Pokemon& defender) const{
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


void PhysicalDamageAndChangeStat::apply_move(Pokemon& attacker,Pokemon& defender) const{
	this->ChangeStat::apply_move(attacker,defender);
	this->PhysicalDamage::apply_move(attacker,defender);
}


void SpecialDamageAndChangeStat::apply_move(Pokemon& attacker,Pokemon& defender) const{
	std::cout << "caca\n";
	this->ChangeStat::apply_move(attacker,defender);
	this->SpecialDamage::apply_move(attacker,defender);
}
