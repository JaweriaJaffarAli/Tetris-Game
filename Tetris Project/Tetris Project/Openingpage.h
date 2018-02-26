

// ------- Includes --------

#include <SDL.h>
#include<SDL_gfx.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>

class MainMenu
{
public:
	MainMenu();
	int initMain();
	void updateScreen();
	void cleanUp();
	void loadBackGround();
};

static SDL_Window  *window;
static SDL_Renderer *render;
static SDL_Surface  *surfacee;
static SDL_Surface  *imgSurfacee;
static SDL_Texture *background_txx;
static SDL_Surface *message = NULL;
static SDL_Surface *message1 = NULL;
static SDL_Surface *message2 = NULL;
static TTF_Font *font = NULL;
static SDL_Color textColor = { 255, 255, 255 };
static SDL_Texture *text;
static SDL_Texture *text1;
static SDL_Texture *text2;

MainMenu::MainMenu()
{
	initMain();
}
void MainMenu::updateScreen()
{
	SDL_RenderPresent(render);
}

int MainMenu::initMain()
{
	
//	const SDL_RendererInfo *info;

	//Uint32 videoflags;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "SDL_Init Error: %s", SDL_GetError());
		return 1;
	}

	if (TTF_Init()<0)
	{
		fprintf(stderr, "TTF_Init Error: %s", TTF_GetError());
	}
	window = SDL_CreateWindow("Tetris",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		600, 550,
		SDL_WINDOW_OPENGL);

	if (window == NULL) {
		fprintf(stderr, "SDL_CreateWindow Error: %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (render == NULL) {
		SDL_DestroyWindow(window);
		fprintf(stderr, "SDL_CreateRenderer Error: %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	
	SDL_Rect MessageRect;
	MessageRect.x = 220; MessageRect.y=220;
	MessageRect.w = 150;  MessageRect.h = 30;

	SDL_Rect MessageRect1;
	MessageRect1.x = 200; MessageRect1.y = 250;
	MessageRect1.w = 180;  MessageRect1.h = 30;

	SDL_Rect MessageRect2;
	MessageRect2.x = 220; MessageRect2.y = 280;
	MessageRect2.w = 150;  MessageRect2.h = 30;

	font = TTF_OpenFont("TimeRoman.ttf", 29);
	
			message = TTF_RenderText_Blended(font, "START ( PRESS 0 )", textColor);
			text = SDL_CreateTextureFromSurface(render, message);
			SDL_FreeSurface(message);
			
			
		
			message1 = TTF_RenderText_Blended(font, "HIGHEST SCORE ( PRESS 1 )", textColor);
			text1 = SDL_CreateTextureFromSurface(render, message1);
			SDL_FreeSurface(message1);
			
			
		
			message2 = TTF_RenderText_Blended(font, "QUIT ( PRESS ESC )", textColor);
			text2 = SDL_CreateTextureFromSurface(render, message2);
			SDL_FreeSurface(message2); 
			
	
	//surface = SDL_GetWindowSurface(win);
	imgSurfacee = SDL_LoadBMP("home.bmp");
    

	background_txx = SDL_CreateTextureFromSurface(render, imgSurfacee);
	SDL_FreeSurface(imgSurfacee);
	SDL_RenderCopy(render, background_txx, NULL, NULL);
	SDL_RenderCopy(render, text, NULL, &MessageRect);
	SDL_RenderCopy(render, text1, NULL, &MessageRect1);
	SDL_RenderCopy(render, text2, NULL, &MessageRect2);
	                                   
	updateScreen();
	return 1;
}

void MainMenu::cleanUp()
{
	SDL_DestroyTexture(background_txx);
	SDL_DestroyRenderer(render);
	SDL_DestroyTexture(text);
	SDL_DestroyWindow(window);
	SDL_Quit();
	TTF_Quit();
}

void MainMenu::loadBackGround()
{
	SDL_RenderCopy(render, background_txx, NULL, NULL);
}

