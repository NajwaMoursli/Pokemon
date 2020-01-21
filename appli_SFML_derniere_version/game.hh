#ifndef DEF_GAME
#define DEF_GAME
#include <iostream>
#include <SFML/Graphics.hpp>
#include "character.hh"


class Game{
private:
	static Character peter;

public:
	static void initialize();
};



#endif