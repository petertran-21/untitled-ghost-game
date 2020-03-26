#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "DisplayObjectContainer.h"
#include "EventDispatcher.h"
#include "PickedUpEvent.h"
#include "QuestManager.h"
#include <vector>
#include <set>
#include "Controller.h"

using namespace std;

class Game : public DisplayObjectContainer {

public:

	/* Singleton pattern */
	static Game* instance;

	int frames_per_sec = 60;
	int windowWidth, windowHeight;

	SDL_Window * window;
	Controller* gameController;
	static SDL_Renderer* renderer;

	//Global frame counter
	static unsigned int frameCounter;

	Game(int windowWidth, int windowHeight);
	virtual ~Game();
	void start();

	virtual void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
	virtual void draw(AffineTransform &at);

private:

	void initSDL();
	void quitSDL();
	set<SDL_Scancode> pressedKeys;

};

#endif
