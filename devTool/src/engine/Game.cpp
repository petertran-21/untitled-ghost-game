#include "Game.h"

/**
 * STATIC REFERENCES
 */
Game* Game::instance;
unsigned int Game::frameCounter = 0;

Game::Game()
{
	Game::instance = this;
	initSDL();
	init();
	TTF_Init();
}

void Game::initSDL()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	IMG_Init(IMG_INIT_PNG);
}

void Game::init()
{
	mouse = new Mouse();
	gameController = new Controller();
	initCameras();
}

void Game::initCameras()
{
	for( int i = 0; i < TOTAL_WINDOWS; i++ )
	{
		cameras[ i ] = new Camera( screenWidths[ i ], screenHeights[ i ] );
		cameras[ i ]->init();
	}
}

Game::~Game()
{
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
		delete cameras[ i ];
	}
}

void Game::quitSDL()
{
	cout << "Quitting SDL" << endl;
	IMG_Quit();
	SDL_Quit();
}

void Game::start()
{
	int ms_per_frame = (1.0/(double)frames_per_sec)*1000;
	clock_t start = clock();

	bool quit = false;
	SDL_Event event;

	while(!quit)
	{
		clock_t end = clock();
		double duration = (( end - start ) / (double) CLOCKS_PER_SEC)*1000;
		if(duration > ms_per_frame)
		{
			//limiting unnecessary update() and draw() calls
			start = end;
			
			Camera* main = cameras[ 0 ];
			Camera* editor = cameras[ 1 ];

			SDL_Renderer* mainRenderer = main->getRenderer();
			SDL_Renderer* editorRenderer = editor->getRenderer();

			main->update( pressedKeys, gameController->getJoystickState(), mainRenderer );
			editor->update( pressedKeys, gameController->getJoystickState(), editorRenderer );

			AffineTransform at;
			main->draw( at, mainRenderer );
			editor->draw( at, editorRenderer );

			frameCounter++;
		}

		while(SDL_PollEvent(&event)) 
		{
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

		//Check window closure
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
		if( cameras[ i ]->isShown() )
		{
			allWindowsClosed = false;
			break;
		}
	}
	return allWindowsClosed;
}

void Game::handleWindowChange( SDL_Keycode windowCode )
{
	switch( windowCode )
	{
		case SDLK_1:
			cameras[ 0 ]->focus();
			break;
		case SDLK_2:
			cameras[ 1 ]->focus();
			break;
	}
}

void Game::passEventToCameras( SDL_Event& event )
{
	for( int i = 0; i < TOTAL_WINDOWS; i++ )
	{
		cameras[ i ]->handleEvent( event );
	}
}
