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
#include "BossImports.h"
#include "particle_system/ParticleEmitter.h"
#include <iostream>
#include <fstream>

using namespace std;

class MyGame : public Game{

public:
	MyGame();
	~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
	virtual void draw(AffineTransform &at);

	Camera* camera;
private:
	Scene* scene_1;

	DisplayObjectContainer* allSprites;
	//DisplayObjectContainer* environment;
	EventDispatcher* controllerDisp;

	//AnimatedSprite* character;
	//MainNPC* npc;
	//Ghost* player;

	DisplayObjectContainer* container;

	EventDispatcher* displayTreeDisp;
	CollisionSystem* collisionSystem;
	DOAddedEvent* DOAdded;
	DORemovedEvent* DORemoved;

	//From UI_WORK
	TweenJuggler* tweenJuggler;
	//Sprite* crocodile;
	Scene* scene_2;
	Sound* soundManager;
	Checklist* checklistTest;
	SelectionMenu* selectionMenuTest;
	TextBox* textboxTest;
	vector<DisplayObject*> inventory;
	Inventory* inventoryUI;
	Map* mapUI;

	DisplayObjectContainer* UIContainer;		// Holds all UI elements as children.

	//bool walking = false;
	//bool transition = false;
	bool UIOpen = false;
	bool InvOpen = false;
	bool mapOpen = false;

	// intro stuff
	AnimatedSprite* startScreen;
	AnimatedSprite* loreScreen1;
	AnimatedSprite* loreScreen2;
	AnimatedSprite* loreScreen3;
	AnimatedSprite* loreScreen4;
	AnimatedSprite* loreScreen5;
	AnimatedSprite* loreScreen6;
	AnimatedSprite* mapTutorial;
	bool playStartSequence = true;
	bool startScreenVisible = true;
	bool fadeStart = false;
	bool lore1ScreenVisible = false;
	bool lore2ScreenVisible = false;
	bool lore3ScreenVisible = false;
	bool lore4ScreenVisible = false;
	bool lore5ScreenVisible = false;
	bool lore6ScreenVisible = false;
	bool fadeLoreIn1 = false;
	bool fadeLoreOut1 = false;
	bool fadeLoreIn2 = false;
	bool fadeLoreOut2 = false;
	bool fadeLoreIn3 = false;
	bool fadeLoreOut3 = false;
	bool fadeLoreIn4 = false;
	bool fadeLoreOut4 = false;
	bool fadeLoreIn5 = false;
	bool fadeLoreOut5 = false;
	bool fadeLoreIn6 = false;
	bool fadeLoreOut6 = false;
	bool screen1Complete = false;
	bool screen2Complete = false;
	bool screen3Complete = false;
	bool screen4Complete = false;
	bool screen5Complete = false;
	bool screen6Complete = false;
	bool mapScreenVisible = false;
	bool townHighlighted = false;

};

#endif
