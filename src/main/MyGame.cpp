#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <algorithm>
#include "MyGame.h"

using namespace std;

MyGame::MyGame() : Game(1000, 1000){
	camera = new Camera();

	allSprites = new DisplayObjectContainer();
	instance->addChild(allSprites);

	container = new DisplayObjectContainer();
	allSprites->addChild(container);

	collisionSystem = new CollisionSystem();
	displayTreeDisp = new EventDispatcher();
	DOAdded = new DOAddedEvent(displayTreeDisp, container);
	DORemoved = new DORemovedEvent(displayTreeDisp, container);
	displayTreeDisp->addEventListener(collisionSystem, DOAddedEvent::DO_ADDED);
	displayTreeDisp->addEventListener(collisionSystem, DORemovedEvent::DO_REMOVED);


	character = new AnimatedSprite("character");
	character->addSpriteSheet("./resources/grendel/Grendel_Idle_Sheet.png", "./resources/grendel/grendel_idle.xml", "idle", 3, 12, true);
	character->addSpriteSheet("./resources/grendel/Grendel_Move_Sheet.png", "./resources/grendel/grendel_move.xml", "move", 4, 12, true);
	container->addChild(character);
	character->drawHitbox();
	character->play("idle");
	DOAdded->addChildCalled(character);
	DOAdded->checkCondition();

}

MyGame::~MyGame(){

}

void MyGame::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
	DORemoved->checkCondition();
	DOAdded->checkCondition();
	collisionSystem->update();
	
	Game::update(pressedKeys, currState);
}

void MyGame::draw(AffineTransform &at){
	//SDL_RenderClear(Game::renderer);
	Game::draw(at);
	//SDL_RenderPresent(Game::renderer);
}
