#include "pokemon.hh"
#include "pokemonFire.hh"
#include <iostream>
#include <string>

using namespace std;

int main(){
	PokemonFire salameche("salameche",10,12,20,35,40,50);
	cout << salameche.toString();
}