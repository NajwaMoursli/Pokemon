#ifndef DEF_TYPE
#define DEF_TYPE
#include <iostream>
#include <vector>
#include <string>

enum Type {Normal,Fire,Water,Grass,Electric,Ice,Dragon,Dark,Ghost,Psychic,Ground,Rock,Steel,Flying,Bug,Poison,Fairy,Fight};
extern std::vector<std::string> typeNames; //on declare la variable globale MAIS on l'initialise dans le .CC
										   //sinon ca merde => (error : "multiple definitions")
										   //extern au lieu de static car extern = globale dans tous les fichiers
															  //alors que static = globale seulement dans le fichier
															  				     //ou la variable est declaree

std::ostream &operator<<(std::ostream &flux,Type const& t);

#endif
