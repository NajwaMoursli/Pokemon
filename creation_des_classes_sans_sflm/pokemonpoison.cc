#include <iostream>
#include <string>
#include "pokemon.hh"
#include "pokemonpoison.hh"

void PokemonPoison::receive_dommage(const Pokemon& p){
	if(p.get_type() == Psychic or p.get_type() == Ground){//si le Pokemon attaque recoit une attaque
																				//qui est du meme type que sa faiblesse
		m_hp -= 50;
	}
	else{
		m_hp -= 25;
	}
}
