#include <iostream>
#include <string>
#include "pokemon.hh"
#include "pokemonground.hh"

void PokemonGround::receive_dommage(const Pokemon& p){
	if(p.get_type() == Water or p.get_type() == Grass or p.get_type() == Ice){//si le Pokemon attaque recoit une attaque
																				//qui est du meme type que sa faiblesse
		m_hp -= 50;
	}
	else{
		m_hp -= 25;
	}
}
