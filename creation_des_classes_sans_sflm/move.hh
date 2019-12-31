#ifndef DEF_MOVE
#define DEF_MOVE

#include <iostream>
#include <string>
#include <vector>
#include "global.hh"


class Pokemon;
class Move{
protected:
	std::string m_name;
	Type m_type;
	std::vector<MoveCategory> m_categories; 
	//Lance flamme :
		//"lance flamme"
		//type = Fire
		//m_categories = {Special,StatEnemy}

public:
	Move(std::string p_name,Type p_type):m_name(p_name),m_type(p_type){}

	//getters
	std::string get_name() const{return(m_name);}
	Type get_type() const{return(m_type	);}
	std::vector<MoveCategory> get_categories() const{return(m_categories);}


	void add_category(MoveCategory mc); //lanceFlamme.add_category(Special)
	bool is_category(MoveCategory mc);
	virtual void apply_move(Pokemon& attacker,Pokemon& defender){}

	std::string toString();
};

//les attaques qui infligent des degats
class Damage : virtual public Move{
protected:
	int m_damage;
public:
	Damage(std::string p_name,Type p_type,int p_damage):Move(p_name,p_type),m_damage(p_damage){}
	int get_damage() const{return(m_damage);}
	virtual void apply_move(Pokemon& attacker,Pokemon& defender){};
};

//les attaques qui infligent des degats physiques
class PhysicalDamage : public Damage{
public:
	PhysicalDamage(std::string p_name,Type p_type,int p_damage):Move(p_name,p_type),Damage(p_name,p_type,p_damage){
		this->Move::add_category(Physical);
	}

	virtual void apply_move(Pokemon& attacker,Pokemon& defender);
};

//les attaques qui infligent des degats speciaux
class SpecialDamage : public Damage{
public:
	SpecialDamage(std::string p_name,Type p_type,int p_damage):Move(p_name,p_type),Damage(p_name,p_type,p_damage){
		this->Move::add_category(Special);
	}

	virtual void apply_move(Pokemon& attacker,Pokemon& defender);
};

//les attaques qui changent les stat soit de son pokemon soit du pokemon adverse
class ChangeStat : virtual public Move{
protected:
	Stat m_statChanged;
	std::string m_modif; //soit augmente soit diminue une stat
	float m_coeffChange;
	bool m_targetIsSelf;

	//Rugissement 
		//"rugissement"
		//type = Normal
		//categories : ChangeStat
		//m_statChanged = Attaque
		//m_modif = "decrease"
		//m_coeffChange = 0.20


public:
	ChangeStat(std::string p_name,Type p_type,Stat p_statChanged,std::string p_modif,int p_coeffChange
		,bool p_targetIsSelf = false):
		Move(p_name,p_type),m_statChanged(p_statChanged),m_modif(p_modif),m_coeffChange(p_coeffChange),
		m_targetIsSelf(p_targetIsSelf){
			if(p_targetIsSelf){
				this->Move::add_category(StatSelf); //attaque qui vise soi-meme
			}
			else{
				this->Move::add_category(StatEnemy); //attaque qui vise l'ennemi
			}
		}

	//getters
	Stat get_statChanged() const{return(m_statChanged);}
	std::string get_modif() const{return(m_modif);} //soit augmente soit diminue une stat
	float get_coeffChange() const{return(m_coeffChange);}		

	void decrease(Pokemon& p);
	void increase(Pokemon& p);
	virtual void apply_move(Pokemon& attacker,Pokemon& defender);
	std::string toString();
};

//les attaques qui infligent des degats physiques et qui changent les stat
class PhysicalDamageAndChangeStat : public PhysicalDamage, public ChangeStat{
public:
	PhysicalDamageAndChangeStat(std::string p_name,Type p_type,int p_damage,Stat p_statChanged,
	std::string p_modif,float p_coeffChange):
		Move(p_name,p_type),
		PhysicalDamage(p_name,p_type,p_damage),
		ChangeStat(p_name,p_type,p_statChanged,p_modif,p_coeffChange)
		{}

	virtual void apply_move(Pokemon& attacker,Pokemon& defender);
};

//les attaques qui infligent des degats speciaux et qui changent les stat
class SpecialDamageAndChangeStat : public SpecialDamage, public ChangeStat{
public:
	SpecialDamageAndChangeStat(std::string p_name,Type p_type,int p_damage,Stat p_statChanged,
	std::string p_modif,float p_coeffChange):
		Move(p_name,p_type),
		SpecialDamage(p_name,p_type,p_damage),
		ChangeStat(p_name,p_type,p_statChanged,p_modif,p_coeffChange)
		{std::cout << "specialdamageandchangestat constructeur\n";}
		
	virtual void apply_move(Pokemon& attacker,Pokemon& defender);
};





#endif