#ifndef MYGAME_H
#define MYGAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "Controller.h"
#include "Scene.h"
#include "EventDispatcher.h"
#include "ClickManager.h"
#include "MouseClickEvent.h"
#include "Camera.h"
#include "TemplateBar.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class MyGame : public Game
{

public:
	MyGame();
	virtual ~MyGame();

private:

	//Main screen
	Camera* main;
	Scene* allSprites;
	TemplateBar* templateBar;

	//Editor screen
	Camera* editor;
	Scene* allComponents;

	//Mouse Observers
	EventDispatcher* mouseDisp;
	MouseClickEvent* mouseClick;
	ClickManager* clickManager;

	bool duplicatedLastFrame = true;
	bool noSpritesSelected = true;
	
};

#endif
