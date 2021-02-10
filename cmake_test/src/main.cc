#include <stdio.h>
#include <SDL2/SDL.h>

bool init();
bool loadMedia();
void close();


const int SCREEN_W = 640;
const int SCREEN_H = 480;

SDL_Window  *gWindow_w = NULL;
SDL_Surface *gWindow_s = NULL;
SDL_Surface *gImage_s  = NULL;

int main(int argc, char **argv)
{
	printf("Hello cmake && SDL2\n");


	if( !init() )
	{
		exit(0);
	}

	if( !loadMedia() )
	{
		exit(0);
	}


	SDL_BlitSurface(gImage_s, NULL, gWindow_s, NULL);
	SDL_UpdateWindowSurface(gWindow_w);
	SDL_Delay(2000);


	close();

	printf("End.\n");
	return 0;
}           


bool init()
{

	if(SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		printf("SDL could not init. SDL_Error:%s\n", SDL_GetError());
		return false;
	}

	gWindow_w = SDL_CreateWindow("SDL2 and CMake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN); 
	if(gWindow_w == NULL)
	{
		printf("SDL could not CreateWindow. SDL_Error:%s\n", SDL_GetError());
		return false;
	}

	gWindow_s = SDL_GetWindowSurface(gWindow_w);
	return true;
}


bool loadMedia()
{
	gImage_s = SDL_LoadBMP("../res/SDL2.bmp");
	if(gImage_s == NULL)
	{
		printf("SDL could not LoadBMP. SDL_Error:%s\n", SDL_GetError());
		return false;
	}
	return true;
}                  


void close()
{
	SDL_FreeSurface(gImage_s);
	gImage_s = NULL;

	SDL_DestroyWindow(gWindow_w);
	gWindow_w = NULL;

	SDL_Quit();
}

