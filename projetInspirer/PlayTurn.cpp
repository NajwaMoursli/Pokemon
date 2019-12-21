#pragma once
#include "PlayTurn.h"
#include "Trainer.h"
#include "Pokemon.h"

// Vérifie si tous les Pokemon sont our 
bool PlayTurn::CheckIfAllFainted(Trainer * opponentPlayer) {

	assert(opponentPlayer -> m_pokemon.size() == 6);// arret execution si nb Pokemon de l'adversaire == 6 (nb max de Pokemon dans une partie)

	for(unsigned int i = 0; i < opponentPlayer -> m_pokemon.size(); i++) {
		if (opponentPlayer -> m_pokemon.at(i)
			-> m_isFainted == false) {
				return false;
		}
	}

	return true;
}

// Verifie si le Pokemon out doit etre changé par un autre 
void PlayTurn::CheckIfNeedSwitch(Trainer * trainer) {

	assert(trainer -> m_pokemon.size() == 6);//arret execution si nb Pokemon du joueur == 6 (nb max de Pokemon dans une partie)


	if(trainer -> m_pokemon.at(trainer -> m_currentPokemon) -> m_isFainted == false) {

		return;//retourne le pokemon du joueur de la partie s'il n'est pas out 

	} else {

		for(unsigned int i = 0; i < trainer -> m_pokemon.size(); i++) {

			if(trainer -> m_pokemon.at(i) -> m_isFainted == false) {

				trainer -> m_currentPokemon = i;
				return;
			}

		}

	}

}

//Partie du pdv de l'utilsateur et ash
BattleState PlayTurn::PlayTurnWhole(Trainer * user, Trainer * ash, Action action) {

	if(PlayTurnUser (user, ash, action) == WON) {
		return WON;
	}

	if(PlayTurnAsh(user, ash) == LOST) {
		return LOST;
	}

	return PLAY;

}

// Au tour de ash
BattleState PlayTurn::PlayTurnAsh(Trainer * user, Trainer * ash) {

	ash -> m_pokemon.at(ash -> m_currentPokemon)
		-> playRandom(user -> m_pokemon.at(user
		-> m_currentPokemon));// ash joue avec n'importe quel pokemon de n'importe quel joeur 

	bool check = CheckIfAllFainted(user);

	if (check == true) {
		return LOST;
	}

	CheckIfNeedSwitch(user);

	return PLAY;

}

// Au tour de l'utilisateur, différente actions possible dans le jeu 
BattleState PlayTurn::PlayTurnUser(Trainer * user, Trainer * ash, Action action) {

	switch(action) {

	case ATTACK:
		{

			user -> m_pokemon.at(user -> m_currentPokemon) ->
				attackNormal(ash -> m_pokemon.at(ash -> m_currentPokemon));

			break;

		}

	case SPECIALATTACK:
		{

			user -> m_pokemon.at(user -> m_currentPokemon) ->
				specialAttack(ash -> m_pokemon.at(ash -> m_currentPokemon));

			break;

		}

	case HEALMOVE:
		{

			user -> m_pokemon.at(user -> m_currentPokemon) -> heal();

			break;

		}

	case CHANGEWEATHER:
		{
			user -> m_pokemon.at(user -> m_currentPokemon) -> changeWeather();

			break;
		}

	case SWITCH:
		{
			break;
		}

	case POTIONMOVE:
		{
			user -> m_item.at(0) -> heal(user -> m_pokemon.at(user -> m_currentPokemon));
			break;
		}

	case SUPERPOTIONMOVE:
		{
			user -> m_item.at(1) -> heal(user -> m_pokemon.at(user -> m_currentPokemon));
			break;
		}

	}

	bool check = CheckIfAllFainted(ash);// si tout les pokemon de ash sont out 

	if (check == true) {
		return WON;// alors le joueur à gagner
	}

	CheckIfNeedSwitch(ash);// si ce n'est pas le cas il change de pokemon 

	return PLAY;// le jeu reprend 
}
