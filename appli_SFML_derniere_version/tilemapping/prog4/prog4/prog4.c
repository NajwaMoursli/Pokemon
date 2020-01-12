#include "fevent.h"

#pragma comment (lib,"sdl.lib")      // ignorez ces lignes si vous ne linkez pas les libs de cette façon.
#pragma comment (lib,"sdlmain.lib")

#define SGN(X) (((X)==0)?(0):(((X)<0)?(-1):(1)))
#define ABS(X) ((((X)<0)?(-(X)):(X)))

int CollisionDecor(SDL_Rect* m,SDL_Rect* n)
{
	if((m->x >= n->x + n->w) 
		|| (m->x + m->w <= n->x) 
		|| (m->y >= n->y + n->h) 
		|| (m->y + m->h <= n->y) 
		) 
		return 0; 
	return 1; 
}

void RecupererVecteur(Input* in,int* vx,int* vy)
{
	int vitesse = 5;
	*vx = *vy = 0;
	if (in->key[SDLK_UP])
		*vy = -vitesse;
	if (in->key[SDLK_DOWN])
		*vy = vitesse;
	if (in->key[SDLK_LEFT])
		*vx = -vitesse;
	if (in->key[SDLK_RIGHT])
		*vx = vitesse;
}

int EssaiDeplacement(SDL_Rect* mur,SDL_Rect* perso,int vx,int vy)
{
	SDL_Rect test;
	test = *perso;
	test.x+=vx;
	test.y+=vy;
	if (CollisionDecor(mur,&test)==0)
	{
		*perso = test;
		return 1;
	}
	return 0;
}

void Affine(SDL_Rect* mur,SDL_Rect* perso,int vx,int vy)
{
	int i;	
    for(i=0;i<ABS(vx);i++)
	{
		if (EssaiDeplacement(mur,perso,SGN(vx),0)==0)
			break;
	}
	for(i=0;i<ABS(vy);i++)
	{
		if (EssaiDeplacement(mur,perso,0,SGN(vy))==0)
			break;			
	}
}

void Deplace(SDL_Rect* mur,SDL_Rect* perso,int vx,int vy)
{
	if (EssaiDeplacement(mur,perso,vx,vy)==1)
		return;
	/*Affine(mur,perso,vx,vy);*/
}

void Evolue(Input* in,SDL_Rect* mur,SDL_Rect* perso)
{
	int vx,vy;
	RecupererVecteur(in,&vx,&vy);
	Deplace(mur,perso,vx,vy);
}

int main(int argc,char** argv)
{
	SDL_Rect mur,perso;
	SDL_Surface* screen;
	Input in;
	memset(&in,0,sizeof(in));
	SDL_Init(SDL_INIT_VIDEO);		// prepare SDL
	screen = SDL_SetVideoMode(800,600,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	mur.x = 450;
	mur.y = 100;
	mur.w = 100;
	mur.h = 200;
	perso.x = 101;
	perso.y = 150;
	perso.w = 50;
	perso.h = 100;
	while(!in.key[SDLK_ESCAPE])
	{
		SDL_Rect copyperso;
		UpdateEvents(&in);
		Evolue(&in,&mur,&perso);
		SDL_FillRect(screen,NULL,0);  // nettoie l'ecran en noir
		SDL_FillRect(screen,&mur,0x800000);  // affiche le mur
		copyperso = perso;
		SDL_FillRect(screen,&copyperso,0x00FF00);  // affiche le perso
		SDL_Flip(screen);
		SDL_Delay(5);
	}
	SDL_Quit();
	return 0;
}
