#include <iostream>

#include <string>

#include "pokemon.hh"

#include "pokemondragon.hh"



void PokemonDragon::receive_dommage(const Pokemon& p){

	if(p.get_type() == Ice or p.get_type() == Dragon or p.get_type() == Fairy){//si le Pokemon attaque recoit une attaque

																				//qui est du meme type que sa faiblesse

		m_hp -= 50;

	}

	else{

		m_hp -= 25;

	}

}
