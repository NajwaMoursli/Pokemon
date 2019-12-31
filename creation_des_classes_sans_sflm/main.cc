#include "global.hh"
#include "move.hh"
#include "pokemon.hh"
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main(){
	//PokemonSteel(std::string p_name,int p_hp,int p_attack,int p_specialAttack,int p_defense,
		//int p_specialDefense,int p_speed,std::vector<Move> p_moves)
	std::vector<Move> movesetEctoplasma = {ballOmbre,exploForce,tonnerre,puissanceCacheeFeu};
	PokemonGhost ectoplasma("Ectoplasma",261,149,270,215,205,285,movesetEctoplasma);
	PokemonGhost ectoplasma2("Ectoplasma",100,10,12,20,40,50,movesetEctoplasma);

	cout << ectoplasma.toString();
	cout << ectoplasma2.toString();

	cout << ectoplasma.movesetToString();	
}

