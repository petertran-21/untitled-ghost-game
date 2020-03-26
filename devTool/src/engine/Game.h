#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "DisplayObjectContainer.h"
#include "DisplayObject.h"
#include "Mouse.h"
#include "Controller.h"
#include "Camera.h"
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

	//Global frame counter
	static unsigned int frameCounter;

	Game(int windowWidth, int windowHeight);
	virtual ~Game();
	void start();

	//Setup internals
	void init();

	virtual void update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState, SDL_Renderer* renderer );
	virtual void draw( AffineTransform &at, SDL_Renderer* renderer );

	int scale = 1;
	int gridWidth;
	int gridHeight;
	static int cellSize;

	//Total windows
	static const int TOTAL_WINDOWS = 2;

	//Our custom windows
	Camera* cameras[ TOTAL_WINDOWS ];

private:

	//Handle events
	void passEventToCameras( SDL_Event& event );

	//Cameras helpers
	void initCameras();
	void destroyCameras();
	void updateCameras();
	bool areAllCamerasClosed();
	void handleWindowChange( SDL_Keycode windowCode );

	void initSDL();
	void quitSDL();
	set<SDL_Scancode> pressedKeys;


};

#endif
