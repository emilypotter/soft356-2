#include "Game.h"
#include <SDL\SDL.h>
#include <iostream>
#include <string>

const int FPS = 60;
const int LOOP_TIME = 1000 / FPS; 


int main(int argc, char* argv[])
{
	Uint32 frameStart, frameTime;

	Game::Instance()->init();

	while (Game::Instance()->isRunning())
	{
		frameStart = SDL_GetTicks();

		Game::Instance()->update();
		Game::Instance()->render();
		Game::Instance()->playSound();

		frameTime = SDL_GetTicks() - frameStart; // time for full 1 loop
		//std::cout <<"frame time = " << frameTime << " milli sec"<< std::endl;

		if (frameTime < LOOP_TIME)
		{
			SDL_Delay((int)(LOOP_TIME - frameTime));
		}

		Game::Instance()->handleEvents();
	}
	Game::Instance()->clean();

	//system("PAUSE");
	return 0;

}