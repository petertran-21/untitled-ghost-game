#ifndef MYGAME_H
#define MYGAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <algorithm>
#include "Game.h"
#include "Sprite.h"
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
#include "Ghost.h"
#include "NPCImports.h"
#include "EnvObjImports.h"
#include "EnvObjImports.h"
#include "CollisionSystem.h"
#include "DOAddedEvent.h"
#include "DORemovedEvent.h"
#include "Tween.h"
#include "Layer.h"
#include "TweenJuggler.h"
#include "CollectiblesImports.h"
#include "UIDefs.h"


using namespace std;

class MyGame : public Game{
	
public:
	MyGame();
	virtual ~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
	virtual void draw(AffineTransform &at);

private:
	Camera* camera;
	Scene* scene_1;
	
	DisplayObjectContainer* allSprites;
	DisplayObjectContainer* environment;
	EventDispatcher* controllerDisp;

	AnimatedSprite* character;
	MainNPC* npc;
	Ghost* player;

	DisplayObjectContainer* container;

	EventDispatcher* displayTreeDisp;
	CollisionSystem* collisionSystem;
	DOAddedEvent* DOAdded;
	DORemovedEvent* DORemoved;

	//From UI_WORK
	TweenJuggler* tweenJuggler;
	Sprite* crocodile;
	Scene* scene_2;
	Sound* new_sound;
	Checklist* checklistTest;
	SelectionMenu* selectionMenuTest;
	TextBox* textboxTest;
	bool walking = false;
	bool transition = false;

};

#endif