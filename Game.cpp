#include "header.h"
#include "Game.h"
#include "Intro.h"
#include "Rules.h"
#include "Player.h"
#include "Battle.h"
#include "Item.h"

//Le jeu n'est pas initialisé car vient de commencer 
Game::GameState Game::stateOfGame = UNINITIALIZED;
sf::RenderWindow Game::window;// Création d'une fenetre 2D grace à SFML

Player Game::user;
Player Game::ash;

DisplayedObject Game::roomBackground;
DisplayedObject Game::exclamationMark;

// Début du jeu
void Game::Start()
{
	//Vérification
	if(stateOfGame != UNINITIALIZED)
		return;

	// Chargement
	window.create(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "Poke Game");

	roomBackground.Load("images/RoomBackground.jpg");
	exclamationMark.Load("images/exclamationMark.png");
	exclamationMark.SetPosition(ASH_X + 2, ASH_Y - 30);

	user.Load("images/User.png");
	user.SetPosition(USER_X, USER_Y);// appel fonction changement position deu personnage de l'utilisateur 

	ash.Load("images/User.png");
	ash.SetPosition(ASH_X, -50);// position personnage systeme (appel de la fonction changement de posistion)

	stateOfGame = Game::INTRO;

	//Le jeu continue jusqu'à que le statut change en "exiting" donc sortie du jeu
	while(stateOfGame != Game::EXITING)
	{
		Loop();
	}

	window.close();
}

// Vérifie quelle scène du jeu s'affiche et le jeu se déroule dans cette scene, différente scene donc utilisation switch/case
void Game::Loop()
{	

	switch(stateOfGame) {

	case Game::ROOM:
		{
			ShowRoom();
			break;
		}

	case Game::ROOMIN:
		{
			ShowRoomIn();
			break;
		}

	case Game::ROOMOUT:
		{
			ShowRoomOut();
			break;
		}

	case Game::BATTLE:
		{
			ShowBattle();
			break;
		}

	case Game::INTRO:
		{
			ShowIntro();
			break;
		}

	case Game::RULES:
		{
			ShowRules();
			break;
		}

	default:
		{
			break;
		}
	}
}

// Affiche l'Intro (début du jeu)
void Game::ShowIntro()
{
	Intro Intro;
	window.clear();
	Intro.show(window);

	//Transition vers RULES
	stateOfGame = RULES;
}

// Affiche les regles du jeu
void Game::ShowRules()
{
	Rules Rule;
	window.clear();
	Rule.show(window);

	// Transistion vers ROMMIN
	stateOfGame = ROOMIN;
}


// Affiche la pièce
void Game::ShowRoom()
{
	
	DrawAllRoom();

	sf::Event currentEvent;// définition des différentes actions sur clavier qui permette de jouer (actions dans le jeu)
	while(true)
	{
		window.waitEvent(currentEvent);

		// Fermer l'écran si on clique sur "Closed"
		if(currentEvent.type == sf::Event::Closed) { 
			stateOfGame = EXITING;
		}

		// Mouvement du joeur
		if(currentEvent.type == sf::Event::KeyPressed)
		{
			if(currentEvent.key.code == sf::Keyboard::Space) {

				stateOfGame = Game::BATTLE;
				return;

			} else if(currentEvent.key.code == sf:: Keyboard::Up) {

				MovePlayer(UP, &user);

			} else if(currentEvent.key.code == sf:: Keyboard::Left) {

				MovePlayer(LEFT, &user);

			} else if(currentEvent.key.code == sf:: Keyboard::Right) {

				MovePlayer(RIGHT, &user);

			} else if(currentEvent.key.code == sf:: Keyboard::Down) {

				MovePlayer(DOWN, &user);

			}

		}

	}

}

// Affiche les scènes coupées du joeur du systeme "ash" entrain de marcher
void Game::ShowRoomIn()
{
	In();
	// Transition vers ROOM
	stateOfGame = ROOM;

}

// Affiche la sortie de ash
void Game::ShowRoomOut()
{
	Out();
	stateOfGame = ROOMIN;
}

//Nouveau combat entre le joueur et ash
void Game::ShowBattle()
{
	Battle battle;
	battle.show(window);
	stateOfGame = ROOMOUT;
}

void Game::DrawAllRoom() {

	window.clear();
	roomBackground.Draw(window);
	user.Draw(window);
	ash.Draw(window);
	window.display();

}

//Deplacement de ash dans le jeu
void Game::In() {

	while(ash.m_y < ASH_Y) {
		MovePlayer(DOWN, &ash);
	}

	exclamationMark.Draw(window);
	window.display();
	sf::sleep(sf::milliseconds(1000));

}

// Deplacement de ash hors du jeu
void Game::Out() {

	while(ash.m_y > 30) {

		MovePlayer(UP, &ash);

	}
}

// Movvement des jambes d'avant en arrière, 4 pas au total
void Game::MovePlayer (Direction direction, Player* movingPlayer) {

	WalkHelper(direction, MOVE_RIGHT_LEG, movingPlayer);
	sf::sleep(sf::milliseconds(100));

	WalkHelper(direction, MOVE_LEFT_LEG, movingPlayer);
	sf::sleep(sf::milliseconds(100));

	WalkHelper(direction, MOVE_RIGHT_LEG, movingPlayer);
	sf::sleep(sf::milliseconds(100));

	WalkHelper(direction, MOVE_LEFT_LEG, movingPlayer);
	sf::sleep(sf::milliseconds(100));

	WalkHelper(direction, STILL, movingPlayer);

}

// Dessin d'un pas à l'écran
void Game::WalkHelper (Direction direction, Action action, Player* movingPlayer) {

	WalkHelperII(direction, action, movingPlayer);// movingPlayer est un ptr de la classe Player 
	movingPlayer -> Move(direction);
	DrawAllRoom();
}

// Chagement de ce pas pour qu'il corresponde sur la Sprite Sheet
void Game::WalkHelperII(Direction direction, Action action, Player* movingPlayer) {

	if(direction == UP) {

		if (action == MOVE_LEFT_LEG) {

			movingPlayer -> m_intRect = sf::IntRect(32, 96, 32, 32);//objet du template sf::Rect<t> pour construire un rectangle

		} else if (action == MOVE_RIGHT_LEG) {

			movingPlayer -> m_intRect = sf::IntRect(96, 96, 32, 32);

		} else {

			movingPlayer -> m_intRect = sf::IntRect(64, 96, 32, 32);

		}

	} else if (direction == DOWN) {

		if (action == MOVE_LEFT_LEG) {

			movingPlayer -> m_intRect = sf::IntRect(32, 0, 32, 32);

		} else if (action == MOVE_RIGHT_LEG) {

			movingPlayer -> m_intRect = sf::IntRect(96, 0, 32, 32);

		} else {

			movingPlayer -> m_intRect = sf::IntRect(64, 0, 32, 32);

		}

	} else if (direction == LEFT) {

		if (action == MOVE_LEFT_LEG) {

			movingPlayer -> m_intRect = sf::IntRect(32, 32, 32, 32);

		} else if (action == MOVE_RIGHT_LEG) {

			movingPlayer -> m_intRect = sf::IntRect(96, 32, 32, 32);

		} else {

			movingPlayer -> m_intRect = sf::IntRect(64, 32, 32, 32);

		}

	} else if (direction == RIGHT) {

		if (action == MOVE_LEFT_LEG) {

			movingPlayer -> m_intRect = sf::IntRect(32, 64, 32, 32);

		} else if (action == MOVE_RIGHT_LEG) {

			movingPlayer -> m_intRect = sf::IntRect(96, 64, 32, 32);

		} else {

			movingPlayer -> m_intRect = sf::IntRect(64, 64, 32, 32);

		}

	}
}
