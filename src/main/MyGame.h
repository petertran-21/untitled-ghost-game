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
#include "Light.h"
#include "Shadow.h"

using namespace std;

class MyGame : public Game{

public:
	MyGame();
	~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
	virtual void draw(AffineTransform &at);

private:
	DisplayObjectContainer* allSprites;
	EventDispatcher* controllerDisp;

	AnimatedSprite* character;
	AnimatedSprite* npc;
	Light* light;
	Shadow* shadow;

	DisplayObjectContainer* container;

	EventDispatcher* displayTreeDisp;
	CollisionSystem* collisionSystem;
	DOAddedEvent* DOAdded;
	DORemovedEvent* DORemoved;


	bool charWalking = false;
	bool npcWalking = false;
	int lastMoved = 3;
	bool transition = false;

};

#endif
