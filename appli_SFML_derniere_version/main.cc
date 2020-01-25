#include <cstdlib>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include "global2.hh"
#include "global.hh"
#include "pokemon.hh"
#include "tilemap.hh"
#include "character.hh"
#include "game.hh"
#include "move.hh"


// using namespace sf;
using namespace std;

// bool tile_is_obstacle(unsigned int i,unsigned int j,const int* tiles,unsigned int width);

int main(int argc, char ** argv){
	cout << "caca\n";
	cout << std::to_string(PokemonDragon::DRACOLOSSE.get_hp()) << ", " << std::to_string(PokemonGhost::GIRATINA.get_hp()) << std::endl;
	Game::launch();
}	