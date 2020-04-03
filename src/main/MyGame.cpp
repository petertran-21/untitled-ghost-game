#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "MyGame.h"

using namespace std;

MyGame::MyGame() : Game(1200, 800){
	new_sound = new Sound();
	new_sound->playSFX("./resources/coin.wav");
	tweenJuggler = new TweenJuggler();
	camera = new Camera();
	
	allSprites = new DisplayObjectContainer();
	instance->addChild(allSprites);

	container = new DisplayObjectContainer();
	allSprites->addChild(container);
	container->addChild(camera);

	collisionSystem = new CollisionSystem();
	displayTreeDisp = new EventDispatcher();
	DOAdded = new DOAddedEvent(displayTreeDisp, container);
	DORemoved = new DORemovedEvent(displayTreeDisp, container);
	displayTreeDisp->addEventListener(collisionSystem, DOAddedEvent::DO_ADDED);
	displayTreeDisp->addEventListener(collisionSystem, DORemovedEvent::DO_REMOVED);

	// CAMERA SHOULD ONLY HAVE SCENES ADDED AS CHILDREN! ANYTHING ELSE MIGHT CAUSE UNDEFINED BEHAVIOR
	scene_1 = new Scene();
	scene_1->loadScene("./resources/scene_1.json");
	camera->addChild(scene_1);

	scene_2 = new Scene();
	scene_2->loadScene("./resources/scene_2.json");
	scene_2->isActive = false;
	camera->addChild(scene_2);


	character = new AnimatedSprite("character");
	character->addSpriteSheet("./resources/character/character_idle.png", "./resources/character/character_animations.xml", "idle", 16, 2, true);
	character->addSpriteSheet("./resources/character/character_walk.png", "./resources/character/character_animations2.xml", "walk", 16, 2, true);
	container->addChild(character);
	character->drawHitbox();
	character->play("idle");

	character->position.x = 600 - (character->width / 2);		// 1/2 screenwidth
	character->position.y = 400 - (character->height / 2);	// 1/2 screenheight

	DOAdded->addChildCalled(character);
	DOAdded->checkCondition();

	// crocodile = new Sprite("crocodile", "./resources/enemies/crocodile.png");
	// container->addChild(crocodile);
	// crocodile->drawHitbox();
	// crocodile->position.x = 300;
	// DOAdded->addChildCalled(crocodile);
	// DOAdded->checkCondition();

	character->createHitbox();
	// crocodile->createHitbox();

	textboxTest = new TextBox("FLIBBERTYGIBBT", 400, 400);
	container->addChild(textboxTest);

	selectionMenuTest = new SelectionMenu();
	selectionMenuTest->addToMenu("Save");
	selectionMenuTest->addToMenu("Load");
	selectionMenuTest->addToMenu("Quit");
	container->addChild(selectionMenuTest);

	checklistTest = new Checklist();
	checklistTest->addEntry("Change Scene");
	container->addChild(checklistTest);
}

MyGame::~MyGame(){
	delete this;
	// delete camera;
}


void MyGame::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
	int speedRate = 10;

	int origPosX = character->position.x;
	tweenJuggler->nextFrame();

	textboxTest->setText(std::to_string(character->position.x));
	if (character->position.x >= 1300 && !transition){
		checklistTest->completeEntry(0);
		transition = true;
		scene_1->isActive = false;
		scene_2->isActive = true;
		Tween* fadeInNewScene = new Tween(scene_2);       // Ideally, TweenJuggler singleton class should delete this, but TweenJuggler doesn't have that implemeented rn.
		fadeInNewScene->animate(TweenableParams::Y, scene_2->position.y - 400, scene_2->position.y, 10.0);
		tweenJuggler->add(fadeInNewScene);
	}
	if (character->position.x < 1300 && transition){
		transition = false;
		scene_1->isActive = true;
		scene_2->isActive = false;
		Tween* fadeInNewScene = new Tween(scene_1);       // Ideally, TweenJuggler singleton class should delete this, but TweenJuggler doesn't have that implemeented rn.
		fadeInNewScene->animate(TweenableParams::Y, scene_1->position.y - 400, scene_1->position.y, 10.0);
		tweenJuggler->add(fadeInNewScene);
	}
	if (pressedKeys.find(SDL_SCANCODE_RETURN) != pressedKeys.end()){
		std::cout << selectionMenuTest->getCurrentlySelected() << std::endl;
	}
	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		character->position.x += 10;
		container->position.x -= 10;
	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		character->position.x -= 10;
		container->position.x += 10;
	}
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		character->position.y += 10;
		container->position.y -= 10;
		selectionMenuTest->incrementPosition();
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		character->position.y -= 10;
		container->position.y += 10;
		selectionMenuTest->decrementPosition();
	}
	if (pressedKeys.find(SDL_SCANCODE_V) != pressedKeys.end()) {
		character->scaleX *= 1.1;
		character->scaleY *= 1.1;
	}
	if (pressedKeys.find(SDL_SCANCODE_B) != pressedKeys.end()) {
		character->scaleX /= 1.1;
		character->scaleY /= 1.1;
	}
	if (pressedKeys.find(SDL_SCANCODE_X) != pressedKeys.end()) {
		character->rotation += 0.1;
	}
	if (pressedKeys.find(SDL_SCANCODE_C) != pressedKeys.end()) {
		character->rotation -= 0.1;
	}

	if (pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end()) {
		container->position.x += 1;
	}
	if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
		container->position.x -= 1;
	}
	if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
		container->position.y += 1;
	}
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
		container->position.y -= 1;
	}
	if (pressedKeys.find(SDL_SCANCODE_F) != pressedKeys.end()) {
		container->scaleX *= 1.1;
		container->scaleY *= 1.1;
	}
	if (pressedKeys.find(SDL_SCANCODE_G) != pressedKeys.end()) {
		container->scaleX /= 1.1;
		container->scaleY /= 1.1;
	}
	if (pressedKeys.find(SDL_SCANCODE_E) != pressedKeys.end()) {
		container->rotation += 0.1;
	}
	if (pressedKeys.find(SDL_SCANCODE_R) != pressedKeys.end()) {
		container->rotation -= 0.1;
	}

/* CROCODILE MOVEMENT NOT NEEDED FOR SFX DEMO OF 4-3-2020

	if (pressedKeys.find(SDL_SCANCODE_L) != pressedKeys.end()) {
		crocodile->position.x += 1;
	}
	if (pressedKeys.find(SDL_SCANCODE_J) != pressedKeys.end()) {
		crocodile->position.x -= 1;
	}
	if (pressedKeys.find(SDL_SCANCODE_K) != pressedKeys.end()) {
		crocodile->position.y += 1;
	}
	if (pressedKeys.find(SDL_SCANCODE_I) != pressedKeys.end()) {
		crocodile->position.y -= 1;
	}
	if (pressedKeys.find(SDL_SCANCODE_N) != pressedKeys.end()) {
		crocodile->scaleX *= 1.1;
		crocodile->scaleY *= 1.1;
	}
	if (pressedKeys.find(SDL_SCANCODE_M) != pressedKeys.end()) {
		crocodile->scaleX /= 1.1;
		crocodile->scaleY /= 1.1;
	}
	if (pressedKeys.find(SDL_SCANCODE_O) != pressedKeys.end()) {
		crocodile->rotation += 0.1;
	}
	if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()) {
		crocodile->rotation -= 0.1;
	}

*/

	/*
 	 * GAME CONTROLLER STUFF
	 */

	// movement
	character->position.x += currState.leftStickX * 5;
	character->position.y += currState.leftStickY * 5;

	// increase scale
	// integer division truncates, so convert to float
	character->scaleX += currState.buttonA / 10.0;
	character->scaleY += currState.buttonA / 10.0;

	// decrease scale
	// integer division truncates, so convert to float
	character->scaleX -= currState.buttonB / 10.0;
	character->scaleY -= currState.buttonB / 10.0;

	if (character->position.x != origPosX){
		if (!walking){
			character->play("walk");
			walking = true;
		}
	} else {
		if (walking){
			character->play("idle");
			walking = false;
		}
	}
	
	//DOAdded->checkCondition();
	//DORemoved->checkCondition();
	collisionSystem->update();
	Game::update(pressedKeys, currState);
}

void MyGame::draw(AffineTransform &at){
	//SDL_RenderClear(Game::renderer);
	Game::draw(at);
}