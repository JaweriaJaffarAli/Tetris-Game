
#ifndef _VIEW_
#define _VIEW_

// ------- Includes --------

#include <SDL.h>
#include<SDL_gfx.h>
#include<iostream>
#include<string>

#endif

#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

enum color {ZERO, BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE, COLOR_MAX}; // Colors

class View {
public:
	std::string ViewScore;
	long double scoreTobeupdated;
    View                ();
	void updatescore(long double score);
    void drawBlock      (int pX1, int pY1, int pX2, int pY2, enum color pC);
    void clearScreen    ();
    int getScreenHeight ();
    int initGraph       ();
    void updateScreen   ();
    void cleanUp        ();
    void loadBackGround ();
    int messageBox      ();
    void loadText       ();
	
};


SDL_Rect scoreBoard;
static SDL_Surface *messageScore;
static TTF_Font *fontScore;
static SDL_Color textColorScore = { 250,250,250 };
static SDL_Texture *textScore;
static SDL_Window  *win;
static SDL_Renderer *ren;
static SDL_Surface  *surface;
static SDL_Surface  *imgSurface;
static SDL_Texture *background_tx;										    // Screen
static Uint32 mColors [COLOR_MAX][4] = {  {0   , 0   , 0   , 0   },
                                          {0x00, 0x00, 0x00, 0xff},					// Colors
                                          {0xff, 0x00, 0x00, 0xff},
                                          {0x00, 0xff, 0x00, 0xff},
                                          {0x00, 0x00, 0xff, 0xff},
                                          {0x00, 0xff, 0xff, 0xff},
                                          {0xff, 0x00, 0xff, 0xff},
                                          {0xff, 0xff, 0x00, 0xff},
                                          {0xff, 0xff, 0xff, 0xff} };

int View::messageBox ()
{
    const SDL_MessageBoxButtonData buttons[] = {
          { /* .flags, .buttonid, .text */        0, 0, "NO" },
          { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "YES" },
      };
    const SDL_MessageBoxColorScheme colorScheme = {
          { /* .colors (.r, .g, .b) */
              /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
              {   0,   0,   0 },
              /* [SDL_MESSAGEBOX_COLOR_TEXT] */
              {   0, 255,   0 },
              /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
              { 255, 255,   0 },
              /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
              { 205, 205, 205 },
              /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
              { 255,   0, 255 }
          }
      };
    const SDL_MessageBoxData messageboxdata = {
            SDL_MESSAGEBOX_INFORMATION, /* .flags */
            NULL, /* .window */
            "GAME OVER!", /* .title */
            "Would you like to play again?", /* .message */
            SDL_arraysize(buttons), /* .numbuttons */
            buttons, /* .buttons */
            &colorScheme /* .colorScheme */
        };

     int buttonid;
     if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
        SDL_Log("error displaying message box");
        return 1;
     }
     if (buttonid == -1) {
         SDL_Log("no selection");
     } else {
         return buttonid;
     }
     return 0;
}
/*
======================================
Init
======================================
*/
View::View()
{
    initGraph();
	scoreTobeupdated = 0;
}

int View::initGraph()
{
	//const SDL_RendererInfo *info;

	//Uint32 videoflags;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		return 1;
	}
	if (TTF_Init() < 0)
	{
		fprintf(stderr, "Error %s", TTF_GetError());
	}

	win = SDL_CreateWindow("Tetris",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		900, 540,
		SDL_WINDOW_OPENGL);

	if (win == NULL) {
		fprintf(stderr, "SDL_CreateWindow Error: %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL) {
		SDL_DestroyWindow(win);
		fprintf(stderr, "SDL_CreateRenderer Error: %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	//surface = SDL_GetWindowSurface(win);
	imgSurface = SDL_LoadBMP("bg.bmp");
	background_tx = SDL_CreateTextureFromSurface(ren, imgSurface);
	SDL_FreeSurface(imgSurface);

	scoreTobeupdated = 0;
	scoreBoard.x = 100;
	scoreBoard.y = 200;
	scoreBoard.h = 30;
	scoreBoard.w = 100;
	ViewScore = std::to_string(scoreTobeupdated);
	fontScore = TTF_OpenFont("TimeRoman.ttf", 20);
	messageScore = TTF_RenderText_Solid(fontScore, ViewScore.c_str(), textColorScore);
	textScore = SDL_CreateTextureFromSurface(ren, messageScore);
	SDL_FreeSurface(messageScore);
	SDL_RenderCopy(ren, background_tx, NULL, NULL);
	SDL_RenderCopy(ren, textScore, NULL, &scoreBoard);

	updateScreen();

	return 1;
	}
	

	


 

/*
=================================================================
drawBlock - Draws the rectangle blocks in the game
=================================================================
*/
void View::drawBlock  (int pX1, int pY1, int pX2, int pY2, enum color pC)
{
    SDL_Rect r = {pX1, pY1, pX2, pY2};
    SDL_SetRenderDrawColor(ren, mColors[pC][0], mColors[pC][1], mColors[pC][2], mColors[pC][3]);
    SDL_RenderFillRect(ren, &r);

}

/*
======================================
Clear the screen to black
======================================
*/
void View::clearScreen ()
{
    color pC = BLACK;
    SDL_SetRenderDrawColor(ren, mColors[pC][0], mColors[pC][1], mColors[pC][2], mColors[pC][3]);
    SDL_RenderClear(ren);
}

// returns screenHeight
int View::getScreenHeight ()
{
    return SDL_GetWindowSurface(win)->h;
}

// updates screen to show all the renderings
void View::updateScreen ()
{
    SDL_RenderPresent(ren);
}

// Loads Background image
void View::loadBackGround()
{

	ViewScore ="SCORE : " + std::to_string(scoreTobeupdated);
	messageScore = TTF_RenderText_Blended(fontScore, ViewScore.c_str(), textColorScore);
	textScore = SDL_CreateTextureFromSurface(ren, messageScore);
	
    SDL_RenderCopy(ren, background_tx, NULL, NULL);
	SDL_RenderCopy(ren, textScore, NULL, &scoreBoard);
	SDL_FreeSurface(messageScore);
}

// Loads text*
void View::loadText ()
{
    TTF_Font* Sans = NULL;
}

void View::cleanUp()
{
    SDL_DestroyTexture(background_tx);
    SDL_DestroyRenderer(ren);
	SDL_DestroyTexture(textScore);
    SDL_DestroyWindow(win);
    SDL_Quit();
	TTF_Quit();
}

void View::updatescore(long double score2)
{
	scoreTobeupdated =static_cast<int>(score2);
}

