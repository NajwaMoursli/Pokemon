#include <iostream>
#include <string>
#include "pokemon.hh"
#include "pokemondark.hh"

void PokemonDark::receive_dommage(const Pokemon& p){
	if(p.get_type() == Fight or p.get_type() == Bug or p.get_type() == Fairy){//si le Pokemon attaque recoit une attaque
																				//qui est du meme type que sa faiblesse
		m_hp -= 50;
	}
	else{
		m_hp -= 25;
	}
}
