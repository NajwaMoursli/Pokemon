#ifndef DEF_MOVE_GLOBAL
#define DEF_MOVE_GLOBAL
#include <iostream>
#include <vector>
#include <map>
#include <string>
// #include "move.hh"

class Move;
class SpecialDamageAndChangeStat;
class SpecialDamageAndChangeStat;
class SpecialDamage;
class PhysicalDamage;

extern const SpecialDamageAndChangeStat ballOmbre;
extern const SpecialDamageAndChangeStat exploForce;
extern const SpecialDamage tonnerre;
extern const SpecialDamage puissanceCacheeFeu;

enum MoveCategory {Physical,Special,StatSelf,StatEnemy};
extern const std::vector<std::string> moveCategoriesNames;
extern const std::map<std::string,Move> movesList;

enum Stat {Attack,SpecialAttack,Defense,SpecialDefense,Speed};
extern const std::vector<std::string> statNames;

enum Type {Fight,Normal,Fire,Water,Grass,Electric,Ice,Dragon,Dark,Ghost,Psychic,Ground,Rock,Steel,Flying,Bug,Poison};
extern const std::vector<std::string> typeNames;
extern const std::map<Type,std::vector<Type>> weaknessesTable;

std::ostream &operator<<(std::ostream &flux,Type const& t);

#endif