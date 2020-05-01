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

	// intro stuff
	startScreen = new AnimatedSprite();
	allSprites->addChild(startScreen);
	startScreen->addAnimation("./resources/start/","main",4,36,true);
	startScreen->width = 1000;
	startScreen->height = 1000;
	startScreen->play("main");

	loreScreen = new AnimatedSprite();
	loreScreen->addAnimation("./resources/start/","lore",1,1,true,"lore");
	loreScreen->width = 1000;
	loreScreen->height = 700;
	loreScreen->position.y = 60;
	loreScreen->alpha = 0;
	loreScreen->play("lore");

	mapTutorial = new AnimatedSprite();
	mapTutorial->addAnimation("./resources/map/", "gameMap", 1, 1, true, "plain");
	mapTutorial->addAnimation("./resources/map/", "tutorial", 12, 60, true, "tutorial");
	mapTutorial->addAnimation("./resources/map/", "townTutorial", 1, 1, true, "townTutorial");
  mapTutorial->addAnimation("./resources/map/", "forestHighlight", 1, 1, true, "forest");
  mapTutorial->addAnimation("./resources/map/", "swampHighlight", 1, 1, true, "swamp");
  mapTutorial->addAnimation("./resources/map/", "beachHighlight", 1, 1, true, "beach");
  mapTutorial->addAnimation("./resources/map/", "mountainsHighlight", 1, 1, true, "mountain");
	mapTutorial->addAnimation("./resources/map/", "townHighlight", 1, 1, true, "town");
	mapTutorial->position.y = 50;
	mapTutorial->width = 1000;
	mapTutorial->height = 700;

	//uncomment following line to check that collision boxes for objects are identical to drawing
	//allSprites->addChild(container);

	collisionSystem = new CollisionSystem(camera, container, inventory);
	displayTreeDisp = new EventDispatcher();
	DOAdded = new DOAddedEvent(displayTreeDisp, container);
	DORemoved = new DORemovedEvent(displayTreeDisp, container);
	displayTreeDisp->addEventListener(collisionSystem, DOAddedEvent::DO_ADDED);
	displayTreeDisp->addEventListener(collisionSystem, DORemovedEvent::DO_REMOVED);

	DOAdded->checkCondition();

	// SFX Menu stuff
	UIContainer = new DisplayObjectContainer();

	inventoryUI = new Inventory(0,0,300,300);
	mapUi = new Map();

	selectionMenuTest = new SelectionMenu(0, 0);
	selectionMenuTest->addToMenu("Stats");
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
	if(playStartSequence) {
		if(pressedKeys.size() > 0 && startScreenVisible) {
			fadeStart = true;
		}
		if(fadeStart) {
			startScreen->alpha = startScreen->alpha - 5;
			if(startScreen->alpha <= 0) {
				startScreenVisible = false;
				fadeStart = false;
			}
		}
		if(!startScreenVisible && !fadeLoreIn && !loreScreenVisible && !fadeLoreOut && !mapScreenVisible) {
			allSprites->removeImmediateChild(startScreen);
			allSprites->addChild(loreScreen);
			fadeLoreIn = true;
		}
		if(fadeLoreIn && !loreScreenVisible) {
			loreScreen->alpha = loreScreen->alpha + 5;
			if(loreScreen->alpha >= 255) {
				loreScreen->alpha = 255;
				loreScreenVisible = true;
				fadeLoreIn = false;
			}
		}
		if(pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end() && loreScreenVisible) {
			fadeLoreOut = true;
		}
		if(fadeLoreOut && loreScreenVisible) {
			loreScreen->alpha = loreScreen->alpha - 5;
			if(loreScreen->alpha <= 0) {
				loreScreen->alpha = 0;
				loreScreenVisible = false;
				fadeLoreOut = false;
			}
		}
		if(!startScreenVisible && !fadeLoreIn && !fadeLoreOut && !loreScreenVisible && !mapScreenVisible) {
			allSprites->removeImmediateChild(loreScreen);
			allSprites->addChild(mapTutorial);
			mapScreenVisible = true;
			mapTutorial->play("tutorial");
		}
		if(mapScreenVisible) {
			if(pressedKeys.find(SDL_SCANCODE_1) != pressedKeys.end()) {
				mapTutorial->play("mountain");
				townHighlighted = false;
			}
			else if(pressedKeys.find(SDL_SCANCODE_2) != pressedKeys.end()) {
				mapTutorial->play("swamp");
				townHighlighted = false;
			}
			else if(pressedKeys.find(SDL_SCANCODE_3) != pressedKeys.end()) {
				mapTutorial->play("forest");
				townHighlighted = false;
			}
			else if(pressedKeys.find(SDL_SCANCODE_4) != pressedKeys.end()) {
				mapTutorial->play("beach");
				townHighlighted = false;
			}
			else if(pressedKeys.find(SDL_SCANCODE_5) != pressedKeys.end()) {
				mapTutorial->play("townTutorial");
				townHighlighted = true;
			}
			if(townHighlighted && pressedKeys.find(SDL_SCANCODE_RETURN) != pressedKeys.end()) {
				//REPLACE BEACH SCENE LOAD PLS town scene load goes here instead
				scene_1->loadScene("./resources/Saves/Slot1/beachEntrance.json", container, inventory);
				allSprites->removeImmediateChild(mapTutorial);
				playStartSequence = false;
			}
		}

		Game::update(pressedKeys, currState);
	}
	else {
		if (!UIOpen){
			if (pressedKeys.find(SDL_SCANCODE_I) != pressedKeys.end() && !InvOpen){
				this->addChild(inventoryUI);
				InvOpen = !InvOpen;
			}
			if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end() && InvOpen){
				this->children.erase(std::remove(this->children.begin(), this->children.end(), inventoryUI), this->children.end());
				InvOpen = !InvOpen;
			}
			if (pressedKeys.find(SDL_SCANCODE_M) != pressedKeys.end() && !mapOpen){
				this->addChild(mapUI);
				mapOpen = !mapOpen;
			}
			if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end() && mapOpen){
				this->children.erase(std::remove(this->children.begin(), this->children.end(), mapUI), this->children.end());
				mapOpen = !mapOpen;
			}

			if (pressedKeys.find(SDL_SCANCODE_N) != pressedKeys.end()){
				camera->getChild(0)->scaleX /= 1.1;
				camera->getChild(0)->scaleY /= 1.1;
			}
			if (pressedKeys.find(SDL_SCANCODE_M) != pressedKeys.end()){
				camera->getChild(0)->scaleX *= 1.1;
				camera->getChild(0)->scaleY *= 1.1;
			}

			DORemoved->checkCondition();
			DOAdded->checkCondition();
			collisionSystem->update();
			Game::update(pressedKeys, currState);
		}
		//cout << "MyGame: Inventory: "<< inventory.size() << endl;
		// cout << "InventoryUI" << inventoryUI->entries.size() << endl;
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
			std::string result = selectionMenuTest->getCurrentlySelected();
			if (result == "Stats"){
				std::string stat = "You've been playing for " + std::to_string(Game::frameCounter/60) + " seconds.";
				textboxTest->setText(stat);
			}
			if (result == "Quit") delete this;		// It *does* quit, yes, but segfaults.
		}
		if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end() && !UIOpen){
			soundManager->playSFX("./resources/sfx/pauseOn.ogg");
			this->addChild(UIContainer);
			textboxTest->setText("Press RETURN to choose option, Q to quit menu.");
			UIOpen = !UIOpen;
		}
		if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end() && UIOpen){
			soundManager->playSFX("./resources/sfx/pauseOff.ogg");
			this->children.erase(std::remove(this->children.begin(), this->children.end(), UIContainer), this->children.end());
			UIOpen = false;
		}
	}
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
}
