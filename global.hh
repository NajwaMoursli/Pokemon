#ifndef DEF_MOVE_GLOBAL
#define DEF_MOVE_GLOBAL
#include <iostream>
#include <vector>
#include <map>
#include <string>


//Les categories existentes des attaques
enum MoveCategory {Physical,Special,StatSelf,StatEnemy};
extern const std::vector<std::string> moveCategoriesNames;

//Les differentes statistiques des pokemon
enum Stat {Attack,SpecialAttack,Defense,SpecialDefense,Speed};
extern const std::vector<std::string> statNames;

//Les differents types des pokemon
enum Type {Fight,Normal,Fire,Water,Grass,Electric,Ice,Dragon,Dark,Ghost,Psychic,Ground,Rock,Steel,Flying,Bug,Poison};
extern const std::vector<std::string> typeNames;
extern const std::map<Type,std::vector<Type>> weaknessesTable;

//Affiche un type sur le terminal, pratique pour les test avant de coder l'interface graphique
std::ostream &operator<<(std::ostream &flux,Type const& t);
std::ostream &operator<<(std::ostream &flux,MoveCategory const& cat);

#endif
