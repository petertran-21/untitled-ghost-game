#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "DisplayObject.h"
#include "MyGame.h"

using namespace std;

MyGame::MyGame() : Game(1200, 1000){
	character = new DisplayObject("character","./resources/character/Idle_1.png");
}

MyGame::~MyGame(){
	delete character;
}


void MyGame::update(set<SDL_Scancode> pressedKeys){
	character->update(pressedKeys);
	Game::update(pressedKeys);
	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		character->position.x++;
		character->facingRight = true;
	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		character->position.x--;
		character->facingRight = false;
	}
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		character->position.y++;
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		character->position.y--;
	}
	if (pressedKeys.find(SDL_SCANCODE_I) != pressedKeys.end()) { // pivot up
		character->pivot.y--;
	}
	if (pressedKeys.find(SDL_SCANCODE_J) != pressedKeys.end()) { // pivot left
		character->pivot.x--;
	}
	if (pressedKeys.find(SDL_SCANCODE_K) != pressedKeys.end()) { // pivot down
		character->pivot.y++;
	}
	if (pressedKeys.find(SDL_SCANCODE_L) != pressedKeys.end()) { // pivot right
		character->pivot.x++;
	}
	if (pressedKeys.find(SDL_SCANCODE_Z) != pressedKeys.end()) { // alpha up
		character->alpha++;
	}
	if (pressedKeys.find(SDL_SCANCODE_X) != pressedKeys.end()) { // alpha down
		character->alpha--;
	}
	if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) { // rotate right
		character->rotation += 0.05;
	}
	if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) { // rotate left
		character->rotation -= 0.05;
	}
	if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end()) { // grow
		character->scaleX *= 1.1;
		character->scaleY *= 1.1;
	}
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) { // shrink
		character->scaleX *= 1.0/1.1;
		character->scaleY *= 1.0/1.1;
	}
	if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()) { // alpha down
		character->visible = false;
	} else character->visible = true;
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);

	SDL_RenderClear(Game::renderer);
	character->draw(at);
	SDL_RenderPresent(Game::renderer);
}