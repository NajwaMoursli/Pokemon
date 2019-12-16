#include "Item.h"
#include "Pokemon.h"

// Constructeur par défaut des élements
Item::Item () {

}

// Définition constructeur
Item::Item(std::string name, int restoreAmount) {

	m_name = name;
	m_restoreAmount = restoreAmount;

}
//Destructeur 
Item::~Item() {

}

// Soigner Pokemon en utilisant une potion ou une superpotion 
void Item::heal(Pokemon * pokemon) { //pokemon est un pointeur de la classe Pokemon

	if(m_name == "SuperPotion") {
		pokemon -> m_health += 50;

		if(pokemon -> m_health >= 100) {
			pokemon -> m_health = 100;
		}

		assert(pokemon -> m_health <= 100 &&  //arreter execution si cette condition est respecté 
			pokemon -> m_health >= 0);

	} else {
		pokemon -> m_health += 20;

		if(pokemon -> m_health >= 100) {
			pokemon -> m_health = 100;
		}

		assert(pokemon -> m_health <= 100 &&
			pokemon -> m_health >= 0);
	}

}
