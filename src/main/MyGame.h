#ifndef MYGAME_H
#define MYGAME_H

#include "Game.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "EventDispatcher.h"
#include "QuestManager.h"
#include "PickedUpEvent.h"
#include "Scene.h"
#include "Sound.h"
#include "Camera.h"
#include "Ghost.h"
#include "NPCImports.h"
#include "EnvObjImports.h"
#include "CollisionSystem.h"
#include "DOAddedEvent.h"
#include "DORemovedEvent.h"
#include "Tween.h"
#include "Layer.h"
#include "TweenJuggler.h"
#include "CollectiblesImports.h"
#include "UIDefs.h"
#include "particle_system/ParticleEmitter.h"

class MyGame : public Game{
	
public:
	MyGame();
	~MyGame();

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

	DisplayObjectContainer* UIContainer;		// Holds all UI elements as children.

	bool walking = false;
	bool transition = false;
	bool UIOpen = false;

};

#endif