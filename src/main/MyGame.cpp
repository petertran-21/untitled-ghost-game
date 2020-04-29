#include "MyGame.h"

MyGame::MyGame() : Game(1000, 1000)
{
	//SFX team work
	camera = new Camera();
	scene_1 = new Scene();
	soundManager = new Sound();
	
	camera->addChild(scene_1);
	this->addChild(camera);

	//Character demo work
	allSprites = new DisplayObjectContainer();
	container = new DisplayObjectContainer();
	instance->addChild(allSprites);

	//uncomment following line to check that collision boxes for objects are identical to drawing
	//allSprites->addChild(container);

	collisionSystem = new CollisionSystem(camera, container);
	displayTreeDisp = new EventDispatcher();
	DOAdded = new DOAddedEvent(displayTreeDisp, container);
	DORemoved = new DORemovedEvent(displayTreeDisp, container);
	displayTreeDisp->addEventListener(collisionSystem, DOAddedEvent::DO_ADDED);
	displayTreeDisp->addEventListener(collisionSystem, DORemovedEvent::DO_REMOVED);

	scene_1->loadScene("./resources/scenes/beachEntrance.json", container);

	DOAdded->checkCondition();
	//-----------------------------------------
	// TODO, SFX will add later

	UIContainer = new DisplayObjectContainer();

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

	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end() && UIOpen){
		selectionMenuTest->incrementPosition();
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end() && UIOpen){
		selectionMenuTest->decrementPosition();
	}
	if (pressedKeys.find(SDL_SCANCODE_RETURN) != pressedKeys.end() && UIOpen){
		std::string result = selectionMenuTest->getCurrentlySelected();
		if (result == "Save");
		if (result == "Load");
		if (result == "Quit") delete this;		// It *does* quit, yes, but segfaults.
	}
	if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end() && !UIOpen){
		soundManager->playSFX("./resources/sfx/pauseOn.ogg");
		this->addChild(UIContainer);
		textboxTest->setText("Press Q to exit the pause menu.");
		UIOpen = !UIOpen;
	}
	if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end() && UIOpen){
		soundManager->playSFX("./resources/sfx/pauseOff.ogg");
		this->children.erase(std::remove(this->children.begin(), this->children.end(), UIContainer), this->children.end());
		UIOpen = false;
	}
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
}