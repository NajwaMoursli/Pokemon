#include "type_enumerate.hh"
#include <iostream>
#include <string>

std::vector<std::string> typeNames = {"Normal","Fire","Water","Grass","Electric","Ice","Dragon","Dark","Ghost","Psychic"
	,"Ground","Rock","Steel","Flying","Bug","Poison","Fairy","Fight"};//typeNames initialisee ici dans le .cc
										   //sinon ca merde => (error : "multiple definitions")

std::ostream &operator<<(std::ostream &flux,Type const& t){
    switch(t){
		case Normal:
			flux << "Normal"; break;
		case Fire:
			flux << "Fire"; break;
		case Steel:
			flux << "Steel"; break;
		case Flying:
			flux << "Flying"; break;
		case Bug:
			flux << "Bug"; break;	
		case Poison:
			flux << "Poison"; break;
		case Water:
			flux << "Water"; break;
		case Grass:
			flux << "Grass"; break;
		case Electric:
			flux << "Electric"; break;
		case Ice:
			flux << "Ice"; break;		
		case Dragon:
			flux << "Dragon"; break;
		case Dark:
			flux << "Dark"; break;		
		case Ghost:
			flux << "Ghost"; break;	
		case Psychic:
			flux << "Psychic"; break;
		case Ground:
			flux << "Ground"; break;
		case Rock:
			flux << "Rock"; break;
		case Fairy:
			flux << "Fairy"; break;
		case Fight:
			flux << "Fight"; break;
	}
    return(flux);
}
