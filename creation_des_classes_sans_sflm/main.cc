#include "global.hh"
#include "move.hh"
#include "pokemon.hh"
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;
// using SpecialDamage::TONNERRE;
// using SpecialDamage::PUISSANCECACHEEFEU;
// using SpecialDamageAndChangeStat::BALLOMBRE;
// using SpecialDamageAndChangeStat::EXPLOFORCE;

int main(){
    //PokemonSteel(std::string p_name,int p_hp,int p_attack,int p_specialAttack,int p_defense,
        //int p_specialDefense,int p_speed,std::vector<Move> p_moves)
	// SpecialDamage fatalFoudre("Fatal Foudre",Electric,80);
	// cout << fatalFoudre.toString();

	/*test moves globaux*/
	// cout << SpecialDamageAndChangeStat::BALLOMBRE.toString();
	// cout << SpecialDamageAndChangeStat::EXPLOFORCE.toString();
	// cout << SpecialDamage::TONNERRE.toString();
	// cout << SpecialDamage::PUISSANCECACHEEFEU.toString();



    PokemonGhost ectoplasma("Ectoplasma",261,149,270,215,205,285,SpecialDamageAndChangeStat::BALLOMBRE,SpecialDamageAndChangeStat::EXPLOFORCE,
    		SpecialDamage::TONNERRE,SpecialDamage::PUISSANCECACHEEFEU);
  	PokemonPsychic ectoplasma2("Ectoplasma",261,149,270,236,102,285,SpecialDamageAndChangeStat::BALLOMBRE,SpecialDamageAndChangeStat::EXPLOFORCE,
    		SpecialDamage::TONNERRE,SpecialDamage::PUISSANCECACHEEFEU);

    cout << ectoplasma.toString();
    cout << ectoplasma2.toString();

    cout << ectoplasma.movesetToString(); 

    //m_moves[0]->get_name();
    // cout << ectoplasma.get_moves()[0]->toString();
    // cout << ectoplasma.get_moves()[1]->toString();
    // cout << ectoplasma.get_moves()[2]->toString();
    // cout << ectoplasma.get_moves()[3]->toString();

    cout << ectoplasma.get_hp() << endl;
    cout << ectoplasma2.get_hp() << endl;
    cout << ectoplasma2.get_specialDefense() << endl;

    int choix;
    cout << "Quelle attaque choisissez-vous ? : ";
    cin >> choix; 
    cout << endl;
    cout << ectoplasma.get_name() + " utilise " + ectoplasma.get_moves()[choix-1]->get_name();

    ectoplasma.get_moves()[choix-1]->apply_move(ectoplasma,ectoplasma2);
    cout << endl;
    cout << ectoplasma.get_hp() << endl;
    cout << ectoplasma2.get_hp() << endl;
    cout << ectoplasma2.get_specialDefense() << endl;




    // SpecialDamage::PUISSANCECACHEEFEU.apply_move(ectoplasma,ectoplasma2);

}


