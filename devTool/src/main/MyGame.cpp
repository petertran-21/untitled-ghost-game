#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Sprite.h"
#include "MyGame.h"

using namespace std;

MyGame::MyGame() : Game(1200, 1000) {
	instance = this;

	allSprites = new DisplayObjectContainer();
	// move that point to the middle
	instance->addChild(allSprites);

	character = new AnimatedSprite("character");
	character->addAnimation("./resources/character/", "Idle", 16, 3, true);

	character->play("Idle");

	character->width = character->height = 100 - (100 % Game::cellSize);
	allSprites->addChild(character);

}

MyGame::~MyGame(){
}


void MyGame::update(set<SDL_Scancode> pressedKeys){

		if (Game::mouse->leftClick) {
			if(character->position.x > Game::mouse->selectBoxX && Game::mouse->selectBoxX > character->position.x + character->width
			&& character->position.y > Game::mouse->selectBoxY && Game::mouse->selectBoxY > character->position.y + character->height) {
				character->selected = false;
			}
			else if(character->position.x > Game::mouse->selectBoxX ||
							Game::mouse->selectBoxX2 > character->position.x + character->width ||
							character->position.y + character->height < Game::mouse->selectBoxY2 ||
							Game::mouse->selectBoxY < character->position.y) {
								character->selected = false;
			}

			else {
				character->selected = true;
			}
		}

		if (character->selected) {
			if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
				character->position.x += Game::cellSize;
			}
			if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
				character->position.x -= Game::cellSize;
			}
			if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
				character->position.y += Game::cellSize;
			}
			if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
				character->position.y -= Game::cellSize;
			}
			if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end()) {
				character->width = Game::cellSize * Game::scale;
				character->height = Game::cellSize * Game::scale;
				Game::scale++;
			}
			if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
				character->width = Game::cellSize * Game::scale;
				character->height = Game::cellSize * Game::scale;
				Game::scale--;
				if (Game::scale < 1) {
					Game::scale = 1;
				}
			}
		}
	Game::update(pressedKeys);
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
}
