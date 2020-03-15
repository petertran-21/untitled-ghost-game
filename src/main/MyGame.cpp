#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Sprite.h"
#include "MyGame.h"


using namespace std;

MyGame::MyGame() : Game(1200, 1000) {
	instance = this;

	allSprites = new DisplayObjectContainer();
	instance->addChild(allSprites);

	//---------- SpriteSheet Demo
	character = new AnimatedSprite("character");
	
	character->addSpriteSheet("./resources/character/character_idle.png", "./resources/character/character_animations.xml", "idle", 16, 2, true);
	character->addSpriteSheet("./resources/character/character_walk.png", "./resources/character/character_animations2.xml", "walk", 16, 2, true);
	allSprites->addChild(character);

	character->play("idle");
	//----------

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
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {

	}
	if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
		character->scaleX *= 1.1;
		character->scaleY *= 1.1;
	}
	if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {

	}
	if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end()) {
		character->rotation += 0.1;
	}
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {

	}
	if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()) {

	}
	if (pressedKeys.find(SDL_SCANCODE_L) != pressedKeys.end()) {

	}

	/*
 	 * GAME CONTROLLER STUFF
	 */ 

	// movement
	const int speedMultiplier = 5;
	character->position.x += currState.leftStickX * speedMultiplier;
	character->position.y += currState.leftStickY * speedMultiplier;

	// increase scale
	// integer division truncates, so convert to float
	const int scaleMultiplier = 10;
	character->scaleX += currState.buttonA / scaleMultiplier;
	character->scaleY += currState.buttonA / scaleMultiplier;

	// decrease scale
	// integer division truncates, so convert to float
	character->scaleX -= currState.buttonB / scaleMultiplier;
	character->scaleY -= currState.buttonB / scaleMultiplier;

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


	Game::update(pressedKeys, currState);
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
}
