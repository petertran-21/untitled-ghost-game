#include "Game.h"

/**
 * STATIC REFERENCES
 */
Game* Game::instance;
SDL_Renderer* Game::renderer;
unsigned int Game::frameCounter = 0;
bool Game::quitGame = false;

Game::Game() : DisplayObjectContainer()
{
	initSDL();
	TTF_Init();

	Game::instance = this;
	this->windowWidth = 1000;
	this->windowHeight = 1000;
	init();
}

Game::Game(int windowWidth, int windowHeight) : DisplayObjectContainer()
{
	initSDL();
	TTF_Init();

	Game::instance = this;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	init();	
}

void Game::initSDL()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	IMG_Init(IMG_INIT_PNG);
}

void Game::init()
{
	gameController = new Controller();
	window = SDL_CreateWindow("Untitled-Ghost-Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->windowWidth, this->windowHeight, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
}

Game::~Game()
{
	quitSDL();
}

void Game::quitSDL(){
	cout << "Quitting SDL" << endl;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
	delete gameController;
	pressedKeys.clear();
	IMG_Quit();
	SDL_Quit();
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
			this->update(pressedKeys, gameController->getJoystickState());
			AffineTransform at;
			this->draw(at);
		}

		if( Game::quitGame ) quit = true;
		SDL_PollEvent(&event);
		gameController->setState(event);
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

void Game::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
	frameCounter++;
	DisplayObjectContainer::update(pressedKeys, currState);
}

void Game::draw(AffineTransform &at){
	SDL_RenderClear(renderer);
	DisplayObjectContainer::draw(at);
	SDL_RenderPresent(renderer);
}