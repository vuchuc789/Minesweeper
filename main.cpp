#define _WIN32_WINNT 0x0500

#include <iostream>
#include <Windows.h>

#include "Game.h"
#include "StartScreen.h"
#include "Map.h"
#include "PlayAgain.h"

const char* WINDOW_TITLE = "Minesweeper";
const int WINDOW_WTDTH = 600;
const int WINDOW_HEIGHT = 900;
const bool FULL_SCREEN = false;

int main(int argc, char* argv[])
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	PlayAgain playagain;

	do
	{
		Game* game = new Game();

		game->Init(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WTDTH, WINDOW_HEIGHT, FULL_SCREEN);

		StartScreen* startScreen = new StartScreen();

		startScreen->pressStart();

		while (startScreen->inputSize())
		{
			SDL_StartTextInput();

			startScreen->handleInput();
			startScreen->renderInput();

			SDL_StopTextInput();
		}

		delete startScreen;

		if (Game::isRunning)
		{
			game->createMap();
			game->printMap();
		}
		while (Game::isRunning)
		{
			game->handleEvents();
			game->render();
		}

		playagain.endScreen(WINDOW_WTDTH, WINDOW_HEIGHT);

		game->cleanGame();

		delete game;

	} while (PlayAgain::playAgain);

	//ShowWindow(hWnd, SW_SHOW);
	//system("pause");
	return 0;
}