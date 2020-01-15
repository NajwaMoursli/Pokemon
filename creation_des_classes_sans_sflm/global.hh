#ifndef DEF_MOVE_GLOBAL
#define DEF_MOVE_GLOBAL
#include <iostream>
#include <vector>
#include <map>
#include <string>


enum MoveCategory {Physical,Special,StatSelf,StatEnemy};
extern const std::vector<std::string> moveCategoriesNames;

enum Stat {Attack,SpecialAttack,Defense,SpecialDefense,Speed};
extern const std::vector<std::string> statNames;

enum Type {Fight,Normal,Fire,Water,Grass,Electric,Ice,Dragon,Dark,Ghost,Psychic,Ground,Rock,Steel,Flying,Bug,Poison};
extern const std::vector<std::string> typeNames;
extern const std::map<Type,std::vector<Type>> weaknessesTable;

enum BattleState { PLAY, LOST, WON }; // ajout etat après combat

std::ostream &operator<<(std::ostream &flux,Type const& t);

#endif
