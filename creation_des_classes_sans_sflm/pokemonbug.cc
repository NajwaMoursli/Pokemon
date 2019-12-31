#include <iostream>
#include <string>
#include "pokemon.hh"
#include "pokemonbug.hh"

void PokemonBug::receive_dommage(const Pokemon& p){
	if(p.get_type() == Fire or p.get_type() == Flying or p.get_type() == Rock){//si le Pokemon attaque recoit une attaque
																				//qui est du meme type que sa faiblesse
		m_hp -= 50;
	}
	else{
		m_hp -= 25;
	}
}
