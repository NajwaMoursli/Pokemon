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

    cout << PokemonGhost::GIRATINA.toString();
    cout << PokemonGhost::ECTOPLASMA.toString();
    cout << PokemonDragon::DRACOLOSSE.toString();
    cout << PokemonGhost::ECTOPLASMA.movesetToString(); 

    //m_moves[0]->get_name();
    // cout << ECTOPLASMA.get_moves()[0]->toString();
    // cout << ECTOPLASMA.get_moves()[1]->toString();
    // cout << ECTOPLASMA.get_moves()[2]->toString();
    // cout << ECTOPLASMA.get_moves()[3]->toString();

    cout << "ectoplasma hp = " << PokemonGhost::ECTOPLASMA.get_hp() << endl;
    cout << "dracolosse hp = " << PokemonDragon::DRACOLOSSE.get_hp() << endl;
    cout << PokemonDragon::DRACOLOSSE.get_specialDefense() << endl;

    int choix;
    cout << "Quelle attaque choisissez-vous ? : ";
    cin >> choix; 
    cout << endl;
    cout << PokemonGhost::ECTOPLASMA.get_name() + " utilise " + PokemonGhost::ECTOPLASMA.get_moves()[choix-1]->get_name();

    PokemonGhost::ECTOPLASMA.get_moves()[choix-1]->apply_move(PokemonGhost::ECTOPLASMA,PokemonDragon::DRACOLOSSE);
    cout << endl;
    cout << "ectoplasma hp = " << PokemonGhost::ECTOPLASMA.get_hp() << endl;
    cout << "dracolosse hp = " << PokemonDragon::DRACOLOSSE.get_hp() << endl;
    cout << PokemonGhost::ECTOPLASMA.get_specialDefense() << endl;




    // SpecialDamage::PUISSANCECACHEEFEU.apply_move(ECTOPLASMA,ECTOPLASMA2);

}


