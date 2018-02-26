#include <windows.h>
#include <stdlib.h>
#include <tchar.h>
#include "Game.h"
#include"Score.h"
#include "Openingpage.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

/*
=========================
main
==========================
*/
int main( int argc, char* args[] )
{
	float score1 = 0;
	PlayerRecord highscore;
	highscore.reterive();
	bool quit = false;
	Commands cmd;
	SDL_Event a;
	MainMenu mainpage;
	int i = 1;
	while (!quit && i != 0 && i!=2)
	{
		int key = cmd.pollkey(&a);
		while (SDL_PollEvent(&a) != 0) {
			if (a.type == SDL_QUIT)
				quit = true;
		}
		//while (SDL_PollEvent(&a)) {
			switch (key)
			{
			/*case SDL_KEYDOWN:
				switch (a.key.keysym.sym)
				{*/
				case (SDLK_0):
				{
					i = 0;
					break;
				}
				case (SDLK_1):
				{
					i = 2;
					break;
				}
				case (SDLK_ESCAPE):
				case (10):
				{
					quit = true;
					break;
				}
				default:
					break;
				}
			//}
		//}
	}
	mainpage.cleanUp();
	if (i == 2)
	{
		highscore.displayall();
		bool exit = false;
		SDL_Event s;
		while (!exit)
		{
			int key = cmd.pollkey(&s);
			while (SDL_PollEvent(&s) != 0) {
				if (a.type == SDL_QUIT)
					quit = true;
			}
			//while (SDL_PollEvent(&a)) {
			switch (key)
			{
				/*case SDL_KEYDOWN:
				switch (a.key.keysym.sym)
				{*/
			
			case (SDLK_ESCAPE):
			case (10):
			{
				exit = true;
				break;
			}
			default:
				break;
			}
			//}
			//}
		}
	}
	highscore.cleanUp();

    // Initializing game objects
    View view;
    Commands cmds;
    int screenHeight = view.getScreenHeight();
    Game game(&view, &cmds, screenHeight);
	
	
    SDL_Event e;

    //Get the actual clock in milliseconds (SDL)
    unsigned long time1 = SDL_GetTicks();

    // ------Main Loop ---------------
    while (!quit)
    {
        game.drawScene(score1);

        int key = cmds.pollkey(&e);
        while(SDL_PollEvent( &e ) != 0){
            if(e.type == SDL_QUIT)
                quit = true;
        }

        //-------input----------
        switch (key)
        {
            case (10):
            {
                quit = true;
            }
            case (SDLK_RIGHT):
            {
                if (game.board->isPossibleMovement (game.posX + 1, game.posY))
                    game.posX++;
                break;
            }
            case (SDLK_LEFT):
            {
                if (game.board->isPossibleMovement (game.posX - 1, game.posY))
                    game.posX--;
                break;
            }
            case (SDLK_DOWN):
            {
                if (game.board->isPossibleMovement (game.posX, game.posY + 1))
                    game.posY++;
                break;
            }
            case (SDLK_SPACE):
            {
                // check collision from up to the possible bottom
                while (game.board->isPossibleMovement(game.posX, game.posY))
                { game.posY++; }

                game.board->storePiece (game.posX, game.posY - 1);

                game.board->deletePossibleLines ();

                if (game.board->isGameOver())
                {
					if(game.restart()) score1 = 0;
					
					else goto exit_loop;
                }
				score1+=20;
                game.createNewPiece();
                break;
            }
            case (SDLK_UP):
            {
                game.piece->rotatePiece();
                if (!game.board->isPossibleMovement (game.posX, game.posY)){
                    int i = 3;
                    game.piece->rotatePiece(3);  //
                }
                break;
            }
        }

        // -------- vertical movement --------------
        unsigned long time2 = SDL_GetTicks();
        if ((time2 - time1) > WAIT_TIME)
        {
            if (game.board->isPossibleMovement(game.posX, game.posY + 1)) {
                game.posY++;
            } else {
                game.board->storePiece (game.posX, game.posY);
                game.board->deletePossibleLines ();
				score1 += 20;
                if(game.board->isGameOver())
                {
					if(game.restart()) score1 = 0;
					
					else
					   break;
                }
                game.createNewPiece();
				
            }

            time1 = SDL_GetTicks();
        }
    }
label:    exit_loop: 
	
    view.cleanUp();
	highscore.add(score1);
	highscore.save();
    return 0;
}
 