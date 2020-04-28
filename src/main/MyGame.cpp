#include "MyGame.h"

MyGame::MyGame() : Game(1000, 1000)
{
	//SFX team work
	camera = new Camera();
	scene_1 = new Scene();
	
	camera->addChild(scene_1);
	this->addChild(camera);

	//Character demo work
	allSprites = new DisplayObjectContainer();
	container = new DisplayObjectContainer();
	instance->addChild(allSprites);

	//uncomment following line to check that collision boxes for objects are identical to drawing
	//allSprites->addChild(container);

	collisionSystem = new CollisionSystem(camera, container, inventory);
	displayTreeDisp = new EventDispatcher();
	DOAdded = new DOAddedEvent(displayTreeDisp, container);
	DORemoved = new DORemovedEvent(displayTreeDisp, container);
	displayTreeDisp->addEventListener(collisionSystem, DOAddedEvent::DO_ADDED);
	displayTreeDisp->addEventListener(collisionSystem, DORemovedEvent::DO_REMOVED);
	

	scene_1->loadScene("./resources/scenes/beachEntrance.json", container, inventory);

	DOAdded->checkCondition();
	//-----------------------------------------
	// TODO, SFX will add later

	UIContainer = new DisplayObjectContainer();

	inventoryUI = new Inventory(0,0,300,300);

	selectionMenuTest = new SelectionMenu(0, 0);
	selectionMenuTest->addToMenu("Save");
	selectionMenuTest->addToMenu("Load");
	selectionMenuTest->addToMenu("Quit");

	textboxTest = new TextBox(0, 400);
	UIContainer->addChild(selectionMenuTest);
	UIContainer->addChild(textboxTest);

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
	if (!UIOpen){
		DORemoved->checkCondition();
		DOAdded->checkCondition();
		collisionSystem->update();
		Game::update(pressedKeys, currState);

		if (pressedKeys.find(SDL_SCANCODE_N) != pressedKeys.end()){
			camera->getChild(0)->scaleX /= 1.1;
			camera->getChild(0)->scaleY /= 1.1;
		}
		if (pressedKeys.find(SDL_SCANCODE_M) != pressedKeys.end()){
			camera->getChild(0)->scaleX *= 1.1;
			camera->getChild(0)->scaleY *= 1.1;
		}
	}
	cout << "MyGame: Inventory: "<< inventory.size() << endl;
	cout << "InventoryUI" << inventoryUI->entries.size() << endl;
	if(inventoryUI->entries.size()!=inventory.size()){
		inventoryUI->entries=inventory; 
	}

	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end() && UIOpen){
		selectionMenuTest->incrementPosition();
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end() && UIOpen){
		selectionMenuTest->decrementPosition();
	}
	if (pressedKeys.find(SDL_SCANCODE_RETURN) != pressedKeys.end() && UIOpen){
		std::cout << selectionMenuTest->getCurrentlySelected() << std::endl;
	}
	if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end() && !UIOpen){
		this->addChild(UIContainer);
		textboxTest->setText("Press Q to exit the pause menu.");
		UIOpen = !UIOpen;
	}
	if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end() && UIOpen){
		this->children.erase(std::remove(this->children.begin(), this->children.end(), UIContainer), this->children.end());
		UIOpen = false;
	}
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
}