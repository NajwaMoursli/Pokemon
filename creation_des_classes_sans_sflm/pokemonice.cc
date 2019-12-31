#include <iostream>

#include <string>

#include "pokemon.hh"

#include "pokemonice.hh"



void PokemonIce::receive_dommage(const Pokemon& p){

	if(p.get_type() == Fire or p.get_type() == Fight or p.get_type() == Rock or p.get-type() == Steel){//si le Pokemon attaque recoit une attaque

																				//qui est du meme type que sa faiblesse

		m_hp -= 50;

	}

	else{

		m_hp -= 25;

	}

}
