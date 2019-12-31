#include <iostream>

#include <string>

#include "pokemon.hh"

#include "pokemongrass.hh"



void PokemonGrass::receive_dommage(const Pokemon& p){

	if(p.get_type() == Fire or p.get_type() == Ice or p.get_type() == Posion or p.get_type() == Flying or p.get_type() == Bug){//si le Pokemon attaque recoit une attaque

																				//qui est du meme type que sa faiblesse

		m_hp -= 50;

	}

	else{

		m_hp -= 25;

	}

}
