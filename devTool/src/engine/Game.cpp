#include <iostream>
#include "Game.h"
#include <string>
#include <ctime>
#include "DisplayObject.h"
#include "Mouse.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

SDL_Renderer* Game::renderer;
Game* Game::instance;
unsigned int Game::frameCounter = 0;
int Game::cellSize = 20;

Game::Game(int windowWidth, int windowHeight){
	Game::instance = this;

	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	gridWidth = windowWidth / cellSize;
	gridHeight = windowHeight / cellSize;

	mouse = new Mouse();
	gameController = new Controller();
	initSDL();
	TTF_Init();
}

Game::~Game(){
	delete mouse;
	quitSDL();
}

void Game::quitSDL(){
	cout << "Quitting sdl" << endl;
	SDL_DestroyRenderer(Game::renderer);
	SDL_DestroyWindow(window);
	SDL_JoystickClose(gameController->getJoystick());

	IMG_Quit();
	SDL_Quit();
}

void Game::initSDL(){
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	IMG_Init(IMG_INIT_PNG);

	window = SDL_CreateWindow("myGame",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->windowWidth, this->windowHeight, 0);

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

	Game::renderer = renderer;
}

void Game::start(){

	int ms_per_frame = (1.0/(double)this->frames_per_sec)*1000;
	std::clock_t start = std::clock();

	bool quit = false;
	SDL_Event event;

	while(!quit){
		std::clock_t end = std::clock();
		double duration = (( end - start ) / (double) CLOCKS_PER_SEC)*1000;
		if(duration > ms_per_frame){
			start = end;
			this->update(pressedKeys);
			AffineTransform at;
			this->draw(at);
		}

		while(SDL_PollEvent(&event)) {
			mouse->setState(event);
			switch (event.type)
			{
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					pressedKeys.insert(event.key.keysym.scancode);
					break;
				case SDL_KEYUP:
					pressedKeys.erase(event.key.keysym.scancode);
					break;
			}
		}
	}
}

void Game::update(set<SDL_Scancode> pressedKeys){
	frameCounter++;
	DisplayObjectContainer::update(pressedKeys);
}

void Game::draw(AffineTransform &at){
	SDL_SetRenderDrawColor(Game::renderer, 120, 120, 120, 1);
  SDL_RenderClear(Game::renderer);

  SDL_SetRenderDrawColor(Game::renderer, 200, 200, 200, 1);
  for (int x = 0; x < 1 + Game::gridWidth * Game::cellSize; x += Game::cellSize) {
      SDL_RenderDrawLine(Game::renderer, x, 0, x, this->windowHeight);
  }
	for (int y = 0; y < 1 + Game::gridHeight * Game::cellSize; y += Game::cellSize) {
      SDL_RenderDrawLine(Game::renderer, 0, y, this->windowWidth, y);
  }
	DisplayObjectContainer::draw(at);
	mouse->drawSelectBox(Game::renderer);
	SDL_RenderPresent(Game::renderer);

}
