#include "Game.h"

using namespace std;

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
	initSDL();

	//Initalize the game
	init();

	TTF_Init();
}

Game::~Game(){
	delete mouse;
	delete gameController;
	pressedKeys.clear();
	destroyCameras();

	quitSDL();
}

void Game::destroyCameras()
{
	for( int i = 0; i < TOTAL_WINDOWS; i++ )
	{
		cameras[ i ].free();
	}
}

void Game::init()
{
	mouse = new Mouse();
	gameController = new Controller();
	initCameras();

	//Add Grid to main screen
	cameras[ 0 ].addGrid();
}

void Game::initCameras()
{
	for( int i = 0; i < TOTAL_WINDOWS; i++ )
	{
		cameras[ i ].init();
	}
}

void Game::quitSDL(){
	cout << "Quitting sdl" << endl;
	SDL_JoystickClose(gameController->getJoystick());

	IMG_Quit();
	SDL_Quit();
}

void Game::initSDL(){
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	IMG_Init(IMG_INIT_PNG);
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
			
			//Get camerasd
			Camera main = cameras[ 0 ];
			Camera editor = cameras[ 1 ];
 
			//Get renderers
			SDL_Renderer* mainRenderer = main.getRenderer();
			SDL_Renderer* editorRenderer = editor.getRenderer();

			//Distribute important data
			main.update( pressedKeys, gameController->getJoystickState(), mainRenderer );
			editor.update( pressedKeys, gameController->getJoystickState(), editorRenderer );

			//Create transformation matrix
			AffineTransform at;

			//Draw screens
			main.draw( at, mainRenderer );
			editor.draw( at, editorRenderer );

			//Update frame counter
			frameCounter++;
		}

		while(SDL_PollEvent(&event)) {
			gameController->setState(event);
			mouse->setState(event);
			passEventToCameras(event);
			switch (event.type)
			{
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					pressedKeys.insert(event.key.keysym.scancode);
					handleWindowChange(event.key.keysym.sym);
					break;
				case SDL_KEYUP:
					pressedKeys.erase(event.key.keysym.scancode);
					break;
			}
		}

		//Re-render cameras
		updateCameras();

		//Check all windows
		bool gameClosed = areAllCamerasClosed();
		if( gameClosed )
		{
			quit = true;
		}
	}
}

bool Game::areAllCamerasClosed()
{
	bool allWindowsClosed = true;
	for( int i = 0; i < TOTAL_WINDOWS; i++ )
	{
		if( cameras[ i ].isShown() )
		{
			allWindowsClosed = false;
			break;
		}
	}
	return allWindowsClosed;
}

void Game::updateCameras()
{
	for( int i = 0; i < TOTAL_WINDOWS; i++ )
	{
		cameras[ i ].render();
	}
}

void Game::handleWindowChange( SDL_Keycode windowCode )
{
	switch( windowCode )
	{
		case SDLK_1:
			cameras[ 0 ].focus();
			break;
		case SDLK_2:
			cameras[ 1 ].focus();
			break;
	}
}

void Game::passEventToCameras( SDL_Event& event )
{
	for( int i = 0; i < TOTAL_WINDOWS; i++ )
	{
		cameras[ i ].handleEvent( event );
	}
}

void Game::update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState, SDL_Renderer* renderer )
{
	DisplayObjectContainer::update( pressedKeys, currState, renderer );
}

void Game::draw( AffineTransform &at, SDL_Renderer* renderer )
{
}
