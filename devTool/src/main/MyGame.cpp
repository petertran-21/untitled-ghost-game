#include "MyGame.h"

MyGame::MyGame() : Game() 
{
	/* Singleton pattern */
	instance = this;

	//Get cameras
	main = cameras[ 0 ];
	editor = cameras[ 1 ];

	//Get scenes
	allSprites = new Scene();
	allComponents = new Scene();

	//Initalize template bar
	templateBar = new TemplateBar(64, 224, 208);

	//Build main tree
	main->addChild( allSprites );
	main->addChild( templateBar );

	//Build editor tree
	editor->addChild( allComponents );

	//Connect cameras to ROOT NODE
	instance->addChild( main );
	instance->addChild( editor );

	//Perform various operations
	main->addGrid();
	templateBar->loadTemplateBar();
	templateBar->fitToBottom( main->getWidth(), main->getHeight() );

	//Initalize mouse observers
	mouseDisp = new EventDispatcher();
	mouseClick = new MouseClickEvent(mouseDisp, templateBar, Game::mouse, allSprites);
	clickManager = new ClickManager();
	mouseDisp->addEventListener(clickManager, MouseClickEvent::TILE_SELECTED);
}

MyGame::~MyGame()
{
	delete allSprites;
	delete allComponents;
	delete templateBar;
	delete mouseDisp;
	delete mouseClick;
	delete clickManager;
}

void MyGame::update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState, SDL_Renderer* renderer )
{
}

void MyGame::draw( AffineTransform &at, SDL_Renderer* renderer )
{
}
