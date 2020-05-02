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

	// stone henge
	loreScreen1 = new AnimatedSprite();
	loreScreen1->addAnimation("./resources/start/","lore",1,1,true,"lore");
	loreScreen1->width = 1000;
	loreScreen1->height = 700;
	loreScreen1->position.y = 60;
	loreScreen1->alpha = 0;
	loreScreen1->play("lore");

	// godly symbols
	loreScreen2 = new AnimatedSprite();
	loreScreen2->addAnimation("./resources/start/","symbols",1,1,true,"symbols");
	loreScreen2->width = 1000;
	loreScreen2->height = 700;
	loreScreen2->position.y = 60;
	loreScreen2->alpha = 0;
	loreScreen2->play("symbols");

	// horn
	loreScreen3 = new AnimatedSprite();
	loreScreen3->addAnimation("./resources/start/","horn",6,36,true,"horn");
	loreScreen3->width = 1000;
	loreScreen3->height = 1000;
	loreScreen3->alpha = 0;
	loreScreen3->play("horn");

	// grendel monster
	loreScreen4 = new AnimatedSprite();
	loreScreen4->addAnimation("./resources/start/","grendelMonster",4,36,true,"monster");
	loreScreen4->width = 1000;
	loreScreen4->height = 1000;
	loreScreen4->alpha = 0;
	loreScreen4->play("monster");

	// grendel ghost
	loreScreen5 = new AnimatedSprite();
	loreScreen5->addAnimation("./resources/start/","grendelGhost",4,36,true,"ghost");
	loreScreen5->width = 800;
	loreScreen5->height = 900;
	loreScreen5->position.x = 150;
	loreScreen5->alpha = 0;
	loreScreen5->play("ghost");

	//grendel ghost colored
	loreScreen6 = new AnimatedSprite();
	loreScreen6->addAnimation("./resources/start/","gren",1,1,true,"ghostColor");
	loreScreen6->width = 450;
	loreScreen6->height = 700;
	loreScreen6->position.x = 250;
	loreScreen6->position.y = 60;
	loreScreen6->alpha = 0;
	loreScreen6->play("ghostColor");

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
	mapUI = new Map();

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
		if(!startScreenVisible && !fadeLoreIn1 && !lore1ScreenVisible && !fadeLoreOut1 && !screen1Complete) {
			allSprites->removeImmediateChild(startScreen);
			allSprites->addChild(loreScreen1);
			fadeLoreIn1 = true;
		}
		if(fadeLoreIn1 && !lore1ScreenVisible) {
			loreScreen1->alpha = loreScreen1->alpha + 5;
			if(loreScreen1->alpha >= 255) {
				loreScreen1->alpha = 255;
				lore1ScreenVisible = true;
				fadeLoreIn1 = false;
			}
		}
		if(pressedKeys.size() > 0 && lore1ScreenVisible) {
			fadeLoreOut1 = true;
		}
		if(fadeLoreOut1 && lore1ScreenVisible) {
			loreScreen1->alpha = loreScreen1->alpha - 5;
			if(loreScreen1->alpha <= 0) {
				loreScreen1->alpha = 0;
				lore1ScreenVisible = false;
				fadeLoreOut1 = false;
				screen1Complete = true;
			}
		}

		//
		if(screen1Complete && !lore1ScreenVisible && !fadeLoreIn2 && !lore2ScreenVisible && !fadeLoreOut2 && !screen2Complete) {
			allSprites->removeImmediateChild(loreScreen1);
			allSprites->addChild(loreScreen2);
			fadeLoreIn2 = true;
		}
		if(fadeLoreIn2 && !lore2ScreenVisible) {
			loreScreen2->alpha = loreScreen2->alpha + 5;
			if(loreScreen2->alpha >= 255) {
				loreScreen2->alpha = 255;
				lore2ScreenVisible = true;
				fadeLoreIn2 = false;
			}
		}
		if(pressedKeys.size() > 0 && lore2ScreenVisible) {
			fadeLoreOut2 = true;
		}
		if(fadeLoreOut2 && lore2ScreenVisible) {
			loreScreen2->alpha = loreScreen2->alpha - 5;
			if(loreScreen2->alpha <= 0) {
				loreScreen2->alpha = 0;
				lore2ScreenVisible = false;
				fadeLoreOut2 = false;
				screen2Complete = true;
			}
		}


		//
		if(screen2Complete && !lore2ScreenVisible && !fadeLoreIn3 && !lore3ScreenVisible && !fadeLoreOut3 && !screen3Complete) {
			allSprites->removeImmediateChild(loreScreen2);
			allSprites->addChild(loreScreen3);
			fadeLoreIn3 = true;
		}
		if(fadeLoreIn3 && !lore3ScreenVisible) {
			loreScreen3->alpha = loreScreen3->alpha + 5;
			if(loreScreen3->alpha >= 255) {
				loreScreen3->alpha = 255;
				lore3ScreenVisible = true;
				fadeLoreIn3 = false;
			}
		}
		if(pressedKeys.size() > 0 && lore3ScreenVisible) {
			fadeLoreOut3 = true;
		}
		if(fadeLoreOut3 && lore3ScreenVisible) {
			loreScreen3->alpha = loreScreen3->alpha - 5;
			if(loreScreen3->alpha <= 0) {
				loreScreen3->alpha = 0;
				lore3ScreenVisible = false;
				fadeLoreOut3 = false;
				screen3Complete = true;
			}
		}
		//

		//
		if(screen3Complete && !lore3ScreenVisible && !fadeLoreIn4 && !lore4ScreenVisible && !fadeLoreOut4 && !screen4Complete) {
			allSprites->removeImmediateChild(loreScreen3);
			allSprites->addChild(loreScreen4);
			fadeLoreIn4 = true;
		}
		if(fadeLoreIn4 && !lore4ScreenVisible) {
			loreScreen4->alpha = loreScreen4->alpha + 5;
			if(loreScreen4->alpha >= 255) {
				loreScreen4->alpha = 255;
				lore4ScreenVisible = true;
				fadeLoreIn4 = false;
			}
		}
		if(pressedKeys.size() > 0 && lore4ScreenVisible) {
			fadeLoreOut4 = true;
		}
		if(fadeLoreOut4 && lore4ScreenVisible) {
			loreScreen4->alpha = loreScreen4->alpha - 5;
			if(loreScreen4->alpha <= 0) {
				loreScreen4->alpha = 0;
				lore4ScreenVisible = false;
				fadeLoreOut4 = false;
				screen4Complete = true;
			}
		}
		//

		//
		if(screen4Complete && !lore4ScreenVisible && !fadeLoreIn5 && !lore5ScreenVisible && !fadeLoreOut5 && !screen5Complete) {
			allSprites->removeImmediateChild(loreScreen4);
			allSprites->addChild(loreScreen5);
			fadeLoreIn5 = true;
		}
		if(fadeLoreIn5 && !lore5ScreenVisible) {
			loreScreen5->alpha = loreScreen5->alpha + 5;
			if(loreScreen5->alpha >= 255) {
				loreScreen5->alpha = 255;
				lore5ScreenVisible = true;
				fadeLoreIn5 = false;
			}
		}
		if(pressedKeys.size() > 0 && lore5ScreenVisible) {
			fadeLoreOut5 = true;
		}
		if(fadeLoreOut5 && lore5ScreenVisible) {
			loreScreen5->alpha = loreScreen5->alpha - 5;
			if(loreScreen5->alpha <= 0) {
				loreScreen5->alpha = 0;
				lore5ScreenVisible = false;
				fadeLoreOut5 = false;
				screen5Complete = true;
			}
		}
		//

		//
		if(screen5Complete && !lore5ScreenVisible && !fadeLoreIn6 && !lore6ScreenVisible && !fadeLoreOut6 && !screen6Complete) {
			allSprites->removeImmediateChild(loreScreen5);
			allSprites->addChild(loreScreen6);
			fadeLoreIn6 = true;
		}
		if(fadeLoreIn6 && !lore6ScreenVisible) {
			loreScreen6->alpha = loreScreen6->alpha + 5;
			if(loreScreen6->alpha >= 255) {
				loreScreen6->alpha = 255;
				lore6ScreenVisible = true;
				fadeLoreIn6 = false;
			}
		}
		if(pressedKeys.size() > 0 && lore6ScreenVisible) {
			fadeLoreOut6 = true;
		}
		if(fadeLoreOut6 && lore6ScreenVisible) {
			loreScreen6->alpha = loreScreen6->alpha - 5;
			if(loreScreen6->alpha <= 0) {
				loreScreen6->alpha = 0;
				lore6ScreenVisible = false;
				fadeLoreOut6 = false;
				screen6Complete = true;
			}
		}
		//

		//
		if(!mapScreenVisible && screen1Complete && screen2Complete && screen3Complete && screen4Complete && screen5Complete && screen6Complete) {
			allSprites->removeImmediateChild(loreScreen6);
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
				mapUI->active = mapOpen;
			}
			if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end() && mapOpen){
				mapOpen = !mapOpen;
				mapUI->active = mapOpen;
				Game::update(pressedKeys, currState);
				this->children.erase(std::remove(this->children.begin(), this->children.end(), mapUI), this->children.end());
			}

			if (pressedKeys.find(SDL_SCANCODE_Z) != pressedKeys.end()){
				camera->getChild(0)->scaleX /= 1.1;
				camera->getChild(0)->scaleY /= 1.1;
			}
			if (pressedKeys.find(SDL_SCANCODE_X) != pressedKeys.end()){
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
