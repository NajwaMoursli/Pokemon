#include "pokemon.hh"
#include "pokemonFire.hh"
#include <iostream>
#include <string>
#include <cstdlib>
#include <SFML/Graphics.hpp> 

using namespace sf;// propre à SFML
using namespace std;

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
