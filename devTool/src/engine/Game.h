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

	Game();

	/* 
	 * SINGLETON DESIGN PATERN
	 */
	static Game* instance;

	//Main game loop
	void start();

	//Polymorphic methods
	virtual ~Game();
	virtual void update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState, SDL_Renderer* renderer );
	virtual void draw( AffineTransform &at, SDL_Renderer* renderer );

	//Game windows
	static const int TOTAL_WINDOWS = 2;
	Camera* cameras[ TOTAL_WINDOWS ];

	//Input Devices
	Mouse* mouse;
	Controller* gameController;

private:

	//Camera helpers methods
	void initCameras();
	void destroyCameras();
	bool areAllCamerasClosed();
	void passEventToCameras( SDL_Event& event );
	void handleWindowChange( SDL_Keycode windowCode );

	//Initalizer methods
	void init();
	void initSDL();
	void quitSDL();

	//Keyboard
	set<SDL_Scancode> pressedKeys;

	//IMPORTANT
	static unsigned int frameCounter;
	const int frames_per_sec = 60;

};

#endif
