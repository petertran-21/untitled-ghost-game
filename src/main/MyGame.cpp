#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
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
	//character->drawBox = true;
	container->addChild(character);
	character->play("idle");
	DOAdded->addChildCalled(character);
	DOAdded->checkCondition();

}

MyGame::~MyGame(){

}

void MyGame::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
	int origPosX = character->position.x;

	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		character->position.x += 1;
	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		character->position.x -= 1;
	}
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		character->position.y += 1;
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		character->position.y -= 1;
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

	if (character->position.x != origPosX){
		if (!walking){
			character->play("move");
			walking = true;
		}
	} else {
		if (walking){
			character->play("idle");
			walking = false;
		}
	}

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
