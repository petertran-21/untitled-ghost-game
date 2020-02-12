#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Sprite.h"
#include "MyGame.h"

using namespace std;

MyGame::MyGame() : Game(1200, 1000) {
	instance = this;
	instance->pivot = {600, 500};
	sun = new Sprite("sun","./resources/solarSystem/Sun_0.png");
	// cout << sun->getWidth() << sun->getHeight();
	sun->position = {600, 500};
	sun->width = sun->height = 100;
	sun->pivot = {15, 15};
	instance->addChild(sun);

	p1container = new DisplayObjectContainer();
	p2container = new DisplayObjectContainer();
	p1container->position = {50, 50};
	p2container->position = {50, 50};
	sun->addChild(p1container);
	sun->addChild(p2container);

	planet1 = new Sprite("planet1","./resources/solarSystem/Planet.png");
	planet1->position = {200, 0};
	planet1->width = planet1->height = 30;
	planet1->pivot = {15, 15};
	p1container->addChild(planet1);

	planet2 = new Sprite("planet2","./resources/solarSystem/Planet.png");
	planet2->position = {300, 0};
	planet2->width = planet2->height = 30;
	planet2->pivot = {15, 15};
	p2container->addChild(planet2);

	moon1_1 = new Sprite("moon1_1", "./resources/solarSystem/Moon.png");
	moon1_1->position = {50, 0};
	moon1_1->width = moon1_1->height = 15;
	planet1->addChild(moon1_1);
}

MyGame::~MyGame(){
}


void MyGame::update(set<SDL_Scancode> pressedKeys){
	// sun = ((DisplayObjectContainer*)instance)->getChild("sun");
	// DisplayObject* p1 = ((DisplayObjectContainer*)sun)->getChild("planet1");
	// DisplayObject* p2 = ((DisplayObjectContainer*)sun)->getChild("planet2");
	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		sun->position.x += 2;
	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		sun->position.x -= 2;
	}
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		sun->position.y += 2;
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		sun->position.y -= 2;
	}
	if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
		// sun->rotation += 0.01;
		p1container->rotation += 0.05;
		p2container->rotation += 0.03;
		planet1->rotation += 0.1;
		p1container->position.x = 100*sin(p1container->rotation);
		p2container->position.x = 100*sin(p2container->rotation);
	}
	if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
		// sun->rotation -= 0.01;
		p1container->rotation -= 0.05;
		p2container->rotation -= 0.03;
		planet1->rotation -= 0.1;
		p1container->position.x = 100*sin(p1container->rotation);
		p2container->position.x = 100*sin(p2container->rotation);
	}
	if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end()) {
		instance->scaleX *= 0.95;
		instance->scaleY *= 0.95;
	}
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
		instance->scaleX *= 1/0.95;
		instance->scaleY *= 1/0.95;
	}
	
	sun->update(pressedKeys);
	Game::update(pressedKeys);
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
}