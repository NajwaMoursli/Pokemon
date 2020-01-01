#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "global.hh"


const std::vector<std::string> typeNames = {"Fight","Normal","Fire","Water","Grass","Electric","Ice","Dragon","Dark","Ghost","Psychic"
	,"Ground","Rock","Steel","Flying","Bug","Poison"};
//enum Type {Fight,Normal,Fire,Water,Grass,Electric,Ice,Dragon,Dark,Ghost,Psychic,Ground,Rock,Steel,Flying,Bug,Poison};

const std::vector<std::string> moveCategoriesNames = {"Physical","Special","StatSelf","StatEnemy"};
const std::vector<std::string> statNames = {"Attack","SpecialAttack","Defense","SpecialDefense","Speed"};

const std::map<Type,std::vector<Type>> weaknessesTable = {
	{Electric,{Ground}},
	{Dragon,{Dragon,Ice}},
	{Dark,{Fight,Bug}},
	{Bug,{Flying,Fire,Rock}},
	{Water,{Electric,Grass}},
	{Steel,{Fire,Ground,Fight}},
	{Psychic,{Ghost,Dark,Bug}},
	{Poison,{Psychic,Ground}},
	{Normal,{Fight}},
	{Ice,{Fire,Fight,Rock,Steel}},
	{Ground,{Water,Grass,Ice}},
	{Grass,{Fire,Ice,Flying,Bug,Poison}},
	{Ghost,{Dark,Ghost}},
	{Flying,{Electric,Ice,Rock}},
	{Fire,{Water,Rock,Ground}},
	{Fight,{Psychic}}
};

// extern const std::map<std::string,Move> movesList = {

// };

std::ostream &operator<<(std::ostream &flux,Stat const& s){
    switch(s){
		case Attack: flux << "Attack"; break;
		case SpecialAttack: flux << "SpecialAttack"; break;
		case Defense: flux << "Defense"; break;		
		case SpecialDefense: flux << "SpecialDefense"; break;		
		case Speed: flux << "Speed"; break;
	}
    return(flux);
}

std::ostream &operator<<(std::ostream &flux,MoveCategory const& cat){
    switch(cat){
		case Physical: flux << "Physical"; break;
		case Special: flux << "Special"; break;
		case StatSelf: flux << "StatSelf"; break;
		case StatEnemy: flux << "StatEnemy"; break;			
	}
    return(flux);
}

std::ostream &operator<<(std::ostream &flux,Type const& t){
    switch(t){
		case Fight: flux << "Fight"; break;    	
		case Normal: flux << "Normal"; break;
		case Fire: flux << "Fire"; break;
		case Steel: flux << "Steel"; break;
		case Flying: flux << "Flying"; break;
		case Bug: flux << "Bug"; break;	
		case Poison: flux << "Poison"; break;
		case Water: flux << "Water"; break;
		case Grass: flux << "Grass"; break;
		case Electric: flux << "Electric"; break;
		case Ice: flux << "Ice"; break;		
		case Dragon: flux << "Dragon"; break;
		case Dark: flux << "Dark"; break;		
		case Ghost: flux << "Ghost"; break;	
		case Psychic: flux << "Psychic"; break;
		case Ground: flux << "Ground"; break;
		case Rock: 	flux << "Rock"; break;			
	}
    return(flux);
}