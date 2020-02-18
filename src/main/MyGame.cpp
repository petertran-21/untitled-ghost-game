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
	allSprites->position = {600, 500};
	instance->addChild(allSprites);

	//---------- Event Demo
	character = new AnimatedSprite("character");
	character->addAnimation("./resources/character/", "Idle", 16, 3, true);
	character->play("Idle");
	character->width = 400; character->height = 400;
	character->position= {0, 0};
	character->pivot = {character->width/2, character->height/2};
	allSprites->addChild(character);

	itemDisp = new EventDispatcher();

	coin = new Sprite("coin", "./resources/items/coin.png");
	coin->width = 100; coin->height = 100;
	coin->position = {200, 0};
	coin->pivot = {coin->width/2, coin->height/2};
	coinEvent = new PickedUpEvent(itemDisp, character, coin);
	allSprites->addChild(coin);

	questManager = new QuestManager();
	itemDisp->addEventListener(questManager, PickedUpEvent::COIN_PICKED_UP);
	//----------


	sun = new AnimatedSprite("sun");
	sun->addAnimation("./resources/solarSystem/", "Sun", 4, 2, true);
	sun->play("Sun");
	// cout << sun->getWidth() << sun->getHeight();
	sun->position = {0, 0};
	sun->width = sun->height = 100;
	sun->pivot = {50, 50};
	allSprites->addChild(sun);

	p1container = new DisplayObjectContainer();
	p2container = new DisplayObjectContainer();
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
	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		character->position.x += 1;
		sun->position.x += 2;
	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		character->position.x -= 1;
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
		allSprites->scaleX *= 1.05;
		allSprites->scaleY *= 1.05;
	}
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
		allSprites->scaleX *= 1/1.05;
		allSprites->scaleY *= 1/1.05;
	}
	if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()) {
		sun->play("Sun");
	}
	if (pressedKeys.find(SDL_SCANCODE_L) != pressedKeys.end()) {
		sun->stop();
	}

	coinEvent->checkCondition();
	Game::update(pressedKeys);
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
	// SDL_RenderClear(Game::renderer);
	// // coin->draw(at);
	// // if(walk) {
	// // 	character->play("walk");
	// // } else {
	// // 	character->play("idle");
	// // }
	// // character->draw(at);
	// SDL_RenderPresent(Game::renderer);
}
