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
#include "QuestManager.h"
#include "PickedUpEvent.h"
#include "Scene.h"
#include "Sound.h"
#include "Camera.h"
#include "Tween.h"
#include "Layer.h"
#include "TweenJuggler.h"
#include "UIDefs.h"

using namespace std;

class MyGame : public Game{
	
public:
	MyGame();
	virtual ~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
	virtual void draw(AffineTransform &at);


private:

	TweenJuggler* tweenJuggler;
	DisplayObjectContainer* allSprites;

	Camera* camera;	
	AnimatedSprite* character;
	Sprite* crocodile;
	DisplayObjectContainer* container;

	EventDispatcher* controllerDisp;

	EventDispatcher* displayTreeDisp;
	CollisionSystem* collisionSystem;
	DOAddedEvent* DOAdded;
	DORemovedEvent* DORemoved;

	Scene* scene_1;
	Scene* scene_2;

	Sound* new_sound;

	Checklist* checklistTest;
	SelectionMenu* selectionMenuTest;
	TextBox* textboxTest;
	
	bool walking = false;
	bool transition = false;

};

#endif
