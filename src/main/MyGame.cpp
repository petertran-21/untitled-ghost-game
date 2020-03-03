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
	allSprites->addChild(character);

	character->play("idle");


	//----------

}

MyGame::~MyGame(){

}


void MyGame::update(set<SDL_Scancode> pressedKeys){
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

	}
	if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {

	}
	if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end()) {

	}
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {

	}
	if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()) {

	}
	if (pressedKeys.find(SDL_SCANCODE_L) != pressedKeys.end()) {

	}


	Game::update(pressedKeys);
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
}
