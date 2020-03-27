#ifndef MYGAME_H
#define MYGAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "AnimatedSprite.h"
#include "EventDispatcher.h"
#include "DOAddedEvent.h"
#include "DORemovedEvent.h"
#include "CollisionSystem.h"
#include "Controller.h"


using namespace std;

class MyGame : public Game{

public:
	MyGame();
	virtual ~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
	virtual void draw(AffineTransform &at);

private:

	DisplayObjectContainer* allSprites;

	AnimatedSprite* character;
	Sprite* crocodile;

	EventDispatcher* controllerDisp;

	EventDispatcher* displayTreeDisp;
	CollisionSystem* collisionSystem;
	DOAddedEvent* DOAdded;
	DORemovedEvent* DORemoved;

	bool walking = false;

};

#endif
