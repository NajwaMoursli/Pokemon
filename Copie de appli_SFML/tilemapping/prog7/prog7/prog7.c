#include "fevent.h"
#include "sprite.h"

#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 600
#define NBSPRITES 5 

void InitSprites(Sprite* sp[NBSPRITES],Animation* An)
{
	int i;
	for(i=0;i<NBSPRITES;i++)
		sp[i] = CreateSprite(100 + 50*i,50 + 100*i,An);
}

void LibererSprites(Sprite* sp[NBSPRITES])
{
	int i;
	for(i=0;i<NBSPRITES;i++)
		LibererSprite(sp[i]);
}


void Render(Sprite* sp[NBSPRITES],SDL_Surface* screen)
{
	int i;
	for(i=0;i<NBSPRITES;i++)
		RenderSprite(sp[i],screen);
}

void EvolueAuto(Sprite* sp[NBSPRITES],int* c)
{
	int i;
	for(i=0;i<NBSPRITES;i++)
	{
		if (i==*c)
			continue;
		if (sp[i]->sens == 0)
		{
			MoveSprite(sp[i],-1,0,marche);
			if (sp[i]->x<100)
				sp[i]->sens = 1;
		}
		if (sp[i]->sens == 1)
		{
			MoveSprite(sp[i],1,0,marche);
			if (sp[i]->x>LARGEUR_FENETRE-100)
				sp[i]->sens = 0;
		}
	}
}

void Evolue(Input* I,Sprite* sp[NBSPRITES],int* c)
{
	if (I->key[SDLK_KP_PLUS])
	{
		I->key[SDLK_KP_PLUS] = 0;
		sp[*c]->stat = arret;
		(*c)++;
		if (*c == NBSPRITES)
			*c = 0;
	}
	sp[*c]->stat = arret;
	if (I->key[SDLK_UP])
		MoveSprite(sp[*c],0,-1,marche);
	else if (I->key[SDLK_DOWN])
		MoveSprite(sp[*c],0,1,marche);
	if (I->key[SDLK_LEFT])
		MoveSprite(sp[*c],-1,0,marche);
	else if (I->key[SDLK_RIGHT])
		MoveSprite(sp[*c],1,0,marche);
	EvolueAuto(sp,c);
}

int main(int argc,char** argv)
{
	Animation* An;
	SDL_Surface* screen;
	Sprite* sp[NBSPRITES];
	Input I;
	int currentsprite = 0;
	SDL_Init(SDL_INIT_VIDEO);		// preapare SDL
	screen = SDL_SetVideoMode(LARGEUR_FENETRE,HAUTEUR_FENETRE,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	An = ChargerAnimation("animat.txt");
	InitSprites(sp,An);
	InitEvents(&I);
	while(!I.key[SDLK_ESCAPE])
	{
		UpdateEvents(&I);
		SDL_FillRect(screen,NULL,0);
		Evolue(&I,sp,&currentsprite);
		Render(sp,screen);
		SDL_Flip(screen);
		SDL_Delay(2);
	}
	LibererSprites(sp);
	LibererAnimation(An);
	return 0;
}
