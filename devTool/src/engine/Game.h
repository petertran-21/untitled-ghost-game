#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "DisplayObjectContainer.h"
#include "DisplayObject.h"
#include "Mouse.h"
#include "Controller.h"
#include <vector>
#include <set>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Game : public DisplayObjectContainer {

public:

	/* Singleton pattern */
	static Game* instance;

	int frames_per_sec = 60;
	int windowWidth, windowHeight;

	Mouse* mouse;
	Controller* gameController;
	SDL_Window * window;
	static SDL_Renderer* renderer;

	//Global frame counter
	static unsigned int frameCounter;

	Game(int windowWidth, int windowHeight);
	virtual ~Game();
	void start();

	virtual void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
	virtual void draw(AffineTransform &at);

	int scale = 1;
	int gridWidth;
	int gridHeight;
	static int cellSize;

private:

	void initSDL();
	void quitSDL();
	set<SDL_Scancode> pressedKeys;


};

#endif
