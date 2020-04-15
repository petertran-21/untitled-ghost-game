#include "MyGame.h"

MyGame::MyGame() : Game(1000, 1000)
{
	//SFX team work
	camera = new Camera();
	scene_1 = new Scene();
	//scene_1->loadScene("./resources/scenes/beachEntrance.json");
	camera->addChild(scene_1);
	instance->addChild(camera);

	//Character demo work
	allSprites = new DisplayObjectContainer();
	container = new DisplayObjectContainer();
	instance->addChild(allSprites);

	//uncomment following line to check that collision boxes for objects are identical to drawing
	//allSprites->addChild(container);

	collisionSystem = new CollisionSystem();
	displayTreeDisp = new EventDispatcher();
	DOAdded = new DOAddedEvent(displayTreeDisp, container);
	DORemoved = new DORemovedEvent(displayTreeDisp, container);
	displayTreeDisp->addEventListener(collisionSystem, DOAddedEvent::DO_ADDED);
	displayTreeDisp->addEventListener(collisionSystem, DORemovedEvent::DO_REMOVED);
	
	player = new Ghost();
	allSprites->addChild(player);

	//DEMO FOR PARTICLE SYSTEM
	player->addChild( new Dot() );
	
	//END DEMO FOR PARTICLE SYSTEM

	DOAdded->addChildCalled(container);
	DOAdded->checkCondition();
	//-----------------------------------------
	// TODO, SFX will add later

	// selectionMenuTest = new SelectionMenu();
	// selectionMenuTest->addToMenu("Save");
	// selectionMenuTest->addToMenu("Load");
	// selectionMenuTest->addToMenu("Quit");
	// container->addChild(selectionMenuTest);

	// checklistTest = new Checklist();
	// checklistTest->addEntry("Change Scene");
	// container->addChild(checklistTest);
}

MyGame::~MyGame()
{
	/**
	 * Don't delete children of "this"
	 * because it's handled automatically through
	 * Game's superclass, DisplayObjectContainer.
	 */

	delete displayTreeDisp;
	delete collisionSystem;
	delete DOAdded;
	delete DORemoved;
}

void MyGame::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
	DORemoved->checkCondition();
	DOAdded->checkCondition();
	collisionSystem->update();
	Game::update(pressedKeys, currState);
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
}
