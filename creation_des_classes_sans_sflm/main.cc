#include "global.hh"
#include "move.hh"
#include "pokemon.hh"
#include <iostream>
#include <string>
<<<<<<< HEAD
#include <map>
#include <vector>
=======
#include <cstdlib>
#include <SFML/Graphics.hpp> 
>>>>>>> 2463ad78a21d1b38168dbe7ad7e97f0ec4df8ed7

using namespace sf;// propre à SFML
using namespace std;

<<<<<<< HEAD
int main(){
	//PokemonSteel(std::string p_name,int p_hp,int p_attack,int p_specialAttack,int p_defense,
		//int p_specialDefense,int p_speed,std::vector<Move> p_moves)
	std::vector<Move> movesetEctoplasma = {ballOmbre,exploForce,tonnerre,puissanceCacheeFeu};
	PokemonGhost ectoplasma("Ectoplasma",261,149,270,215,205,285,movesetEctoplasma);
	PokemonGhost ectoplasma2("Ectoplasma",100,10,12,20,40,50,movesetEctoplasma);

	cout << ectoplasma.toString();
	cout << ectoplasma2.toString();

	cout << ectoplasma.movesetToString();	
}

=======
int main()
{
	RenderWindow app(VideoMode(800, 600, 32), "Jeu Pokemon  ! ",, Style::Close | Style::Titlebar);
	Image image;
	Sprite sprite;

if (!image.LoadFromFile("image.jpg")) // Si le chargement du fichier a échoué
{
    cout<<"Erreur durant le chargement de l'image"<<endl;
    return EXIT_FAILURE; // On ferme le programme
}
else // Si le chargement de l'image a réussi
{
    sprite.SetImage(image); 
}


    // Boucle principale
    while (app.IsOpened())
    {
        Event event;

        while (app.GetEvent(event))
        {
            if (event.Type == Event::Closed)
                app.Close();
        }

        // Remplissage de l'écran (couleur noire par défaut)
        app.Clear();

        // Affichage de la fenêtre à l'écran
        app.Display();
    }
    return EXIT_SUCCESS
	//PokemonFire salameche("salameche",10,12,20,35,40,50);
	//cout << salameche.toString();
}
>>>>>>> 2463ad78a21d1b38168dbe7ad7e97f0ec4df8ed7
