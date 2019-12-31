#ifndef DEF_POKEMON
#define DEF_POKEMON
#include <iostream>
#include <string>
#include <vector>
#include "global.hh"
#include "move.hh"

class Pokemon{
protected:
	std::string m_name;
	Type m_type;
	int m_level;
	int m_hp; //points de vie
	int m_attack;
	int m_specialAttack;
	int m_defense;
	int m_specialDefense;
	int m_speed;
	std::vector<Move> m_moves; 

public:
	//constructeur par liste d'initialisation qui initialise tous les attributs d'une instance de Pokemon
	Pokemon(std::string p_name,Type p_type,int p_level,int p_hp,int p_attack,int p_specialAttack,
		int p_defense,int p_specialDefense,int p_speed,std::vector<Move> p_moves):
		m_name(p_name),m_type(p_type),m_level(p_level),m_hp(p_hp),m_attack(p_attack),
		m_specialAttack(p_specialAttack),m_defense(p_defense),m_specialDefense(p_specialDefense),
		m_speed(p_speed),m_moves(p_moves){}

	//getters
	std::vector<Move> get_moves() const{return(m_moves);}
	std::string get_name() const{return(m_name);}
	Type get_type() const{return(m_type);}
	int get_hp() const{return(m_hp);}
	int get_attack() const{return(m_attack);}
	int get_specialAttack() const{return(m_specialAttack);}
	int get_defense() const{return(m_defense);}
	int get_specialDefense() const{return(m_specialDefense);}
	int get_speed() const{return(m_speed);}

	//setters
	void set_hp(int p_hp){m_hp = p_hp;}
	void set_attack(int p_attack){m_attack = p_attack;}
	void set_specialAttack(int p_specialAttack){m_specialAttack = p_specialAttack;}
	void set_defense(int p_defense){m_defense = p_defense;}
	void set_specialDefense(int p_specialDefense){m_specialDefense = p_specialDefense;}
	void set_speed(int p_speed){m_speed = p_speed;}

	bool is_ko() const{if(m_hp == 0){return(true);}else{return(false);}}
	std::string toString(); //retourne une string qui decrit un pokemon
	std::string movesetToString();
	virtual void receive_dommage(const Pokemon& p) = 0;//applique les dommages recues par un pokemon, version non definitive !
													   //virtuelle car chaque Pokemon recoit des degats differents en fonction
													   //de son type et donc de ses faiblesses et de ses avantages
};

class PokemonFire : public Pokemon{
public:
	PokemonFire(std::string p_name,int p_hp,int p_attack,int p_specialAttack,int p_defense,
		int p_specialDefense,int p_speed,std::vector<Move> p_moves):
		Pokemon(p_name,Fire,100,p_hp,p_attack,p_specialAttack,p_defense,p_specialDefense,p_speed,p_moves){}
	virtual void receive_dommage(const Pokemon& p);
};

class PokemonWater : public Pokemon{
public:
	PokemonWater(std::string p_name,int p_hp,int p_attack,int p_specialAttack,int p_defense,
		int p_specialDefense,int p_speed,std::vector<Move> p_moves):
		Pokemon(p_name,Water,100,p_hp,p_attack,p_specialAttack,p_defense,p_specialDefense,p_speed,p_moves){}
	virtual void receive_dommage(const Pokemon& p);
};

class PokemonSteel : public Pokemon{
public:
	PokemonSteel(std::string p_name,int p_hp,int p_attack,int p_specialAttack,int p_defense,
		int p_specialDefense,int p_speed,std::vector<Move> p_moves):
		Pokemon(p_name,Steel,100,p_hp,p_attack,p_specialAttack,p_defense,p_specialDefense,p_speed,p_moves){}
	virtual void receive_dommage(const Pokemon& p);
};

class PokemonPsychic : public Pokemon{

public:
	PokemonPsychic(std::string p_name,int p_hp,int p_attack,int p_specialAttack,int p_defense,
		int p_specialDefense,int p_speed,std::vector<Move> p_moves):
		Pokemon(p_name,Psychic,100,p_hp,p_attack,p_specialAttack,p_defense,p_specialDefense,p_speed,p_moves){}
	virtual void receive_dommage(const Pokemon& p);
};

class PokemonPoison : public Pokemon{
public:
	PokemonPoison(std::string p_name,int p_hp,int p_attack,int p_specialAttack,int p_defense,
		int p_specialDefense,int p_speed,std::vector<Move> p_moves):
		Pokemon(p_name,Poison,100,p_hp,p_attack,p_specialAttack,p_defense,p_specialDefense,p_speed,p_moves){}
	virtual void receive_dommage(const Pokemon& p);
};

class PokemonNormal : public Pokemon{
public:
	PokemonNormal(std::string p_name,int p_hp,int p_attack,int p_specialAttack,int p_defense,
		int p_specialDefense,int p_speed,std::vector<Move> p_moves):
		Pokemon(p_name,Normal,100,p_hp,p_attack,p_specialAttack,p_defense,p_specialDefense,p_speed,p_moves){}
};

class PokemonIce : public Pokemon{
public:
	PokemonIce(std::string p_name,int p_hp,int p_attack,int p_specialAttack,int p_defense,
		int p_specialDefense,int p_speed,std::vector<Move> p_moves):
		Pokemon(p_name,Ice,100,p_hp,p_attack,p_specialAttack,p_defense,p_specialDefense,p_speed,p_moves){}
	virtual void receive_dommage(const Pokemon& p);
};

class PokemonGround : public Pokemon{
public:
	PokemonGround(std::string p_name,int p_hp,int p_attack,int p_specialAttack,int p_defense,
		int p_specialDefense,int p_speed,std::vector<Move> p_moves):
		Pokemon(p_name,Ground,100,p_hp,p_attack,p_specialAttack,p_defense,p_specialDefense,p_speed,p_moves){}
	virtual void receive_dommage(const Pokemon& p);
};

class PokemonGrass : public Pokemon{
public:
	PokemonGrass(std::string p_name,int p_hp,int p_attack,int p_specialAttack,int p_defense,
		int p_specialDefense,int p_speed,std::vector<Move> p_moves):
		Pokemon(p_name,Grass,100,p_hp,p_attack,p_specialAttack,p_defense,p_specialDefense,p_speed,p_moves){}
	virtual void receive_dommage(const Pokemon& p);
};

class PokemonGhost : public Pokemon{
public:
	PokemonGhost(std::string p_name,int p_hp,int p_attack,int p_specialAttack,int p_defense,
		int p_specialDefense,int p_speed,std::vector<Move> p_moves):
		Pokemon(p_name,Ghost,100,p_hp,p_attack,p_specialAttack,p_defense,p_specialDefense,p_speed,p_moves){}
	virtual void receive_dommage(const Pokemon& p);
};

class PokemonFlying : public Pokemon{
public:
	PokemonFlying(std::string p_name,int p_hp,int p_attack,int p_specialAttack,int p_defense,
		int p_specialDefense,int p_speed,std::vector<Move> p_moves):
		Pokemon(p_name,Flying,100,p_hp,p_attack,p_specialAttack,p_defense,p_specialDefense,p_speed,p_moves){}
	virtual void receive_dommage(const Pokemon& p);
};

class PokemonFight : public Pokemon{
public:
	PokemonFight(std::string p_name,int p_hp,int p_attack,int p_specialAttack,int p_defense,
		int p_specialDefense,int p_speed,std::vector<Move> p_moves):
		Pokemon(p_name,Fight,100,p_hp,p_attack,p_specialAttack,p_defense,p_specialDefense,p_speed,p_moves){}
	virtual void receive_dommage(const Pokemon& p);
};

class PokemonElectric : public Pokemon{
public:
	PokemonElectric(std::string p_name,int p_hp,int p_attack,int p_specialAttack,int p_defense,
		int p_specialDefense,int p_speed,std::vector<Move> p_moves):
		Pokemon(p_name,Electric,100,p_hp,p_attack,p_specialAttack,p_defense,p_specialDefense,p_speed,p_moves){}
	virtual void receive_dommage(const Pokemon& p);

};

class PokemonDragon : public Pokemon{
public:
	PokemonDragon(std::string p_name,int p_hp,int p_attack,int p_specialAttack,int p_defense,
		int p_specialDefense,int p_speed,std::vector<Move> p_moves):
		Pokemon(p_name,Dragon,100,p_hp,p_attack,p_specialAttack,p_defense,p_specialDefense,p_speed,p_moves){}
	virtual void receive_dommage(const Pokemon& p);
};

class PokemonDark : public Pokemon{
public:
	PokemonDark(std::string p_name,int p_hp,int p_attack,int p_specialAttack,int p_defense,
		int p_specialDefense,int p_speed,std::vector<Move> p_moves):
		Pokemon(p_name,Dark,100,p_hp,p_attack,p_specialAttack,p_defense,p_specialDefense,p_speed,p_moves){}
	virtual void receive_dommage(const Pokemon& p);

};

class PokemonBug : public Pokemon{
public:
	PokemonBug(std::string p_name,int p_hp,int p_attack,int p_specialAttack,int p_defense,
		int p_specialDefense,int p_speed,std::vector<Move> p_moves):
		Pokemon(p_name,Bug,100,p_hp,p_attack,p_specialAttack,p_defense,p_specialDefense,p_speed,p_moves){}
	virtual void receive_dommage(const Pokemon& p);

};


#endif