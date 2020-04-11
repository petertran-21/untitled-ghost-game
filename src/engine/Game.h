#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "DisplayObjectContainer.h"
#include "DisplayObject.h"
#include "EventDispatcher.h"
#include "PickedUpEvent.h"
#include "QuestManager.h"
#include "Controller.h"
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <set>



using namespace std;

class Game : public DisplayObjectContainer {

public:

	Game(int windowWidth, int windowHeight);
	Game();
	~Game();

	//Singleton design pattern
	static Game* instance;

	//Static allows for global reference
	static SDL_Renderer* renderer;
	static unsigned int frameCounter;

	void start();
	virtual void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
	virtual void draw(AffineTransform &at);

private:

	void init();
	void initSDL();
	void quitSDL();

	set<SDL_Scancode> pressedKeys;
	Controller* gameController;
	SDL_Window* window;
	const int frames_per_sec = 60;
	int windowWidth;
	int windowHeight;

};

#endif
