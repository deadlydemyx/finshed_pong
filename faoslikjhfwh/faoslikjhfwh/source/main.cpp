//////////////////////////////////////////////////////////////////////////
#include "AIE.h"
#include <string>
#include <cmath>
#include <time.h>
#include <assert.h>
#include <crtdbg.h>
#include <iostream>
#include "gameobj.h"

const int IScreenWidth = 1280;
const int IScreenHeight = 780;

bool gameOver;
bool exits = false;

int main( int argc, char* argv[] )
{	 
		exits = false;
		gameOver = false;
		menu();
		Initialise(1280, 780, false );
		
		initGame();
	
		do 
		{
	
			ClearScreen();

			updateGame(gameOver);

			drawGame();

			if (gameOver == true) 	// loop to break out of game if game is over
				break;

			} while( FrameworkUpdate() == false );
		destroyGame();
		
		 Shutdown();
	

	return 0;
}

