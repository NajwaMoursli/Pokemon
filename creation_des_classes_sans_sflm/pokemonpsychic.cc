#include <iostream>
#include <string>
#include "pokemon.hh"
#include "pokemonpsychic.hh"

void PokemonPsychic::receive_dommage(const Pokemon& p){
	if(p.get_type() == Bug or p.get_type() == Ghost or p.get_type() == Dark){//si le Pokemon attaque recoit une attaque
																				//qui est du meme type que sa faiblesse
		m_hp -= 50;
	}
	else{
		m_hp -= 25;
	}
}
