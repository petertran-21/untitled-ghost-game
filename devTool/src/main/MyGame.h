#ifndef MYGAME_H
#define MYGAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "Scene.h"
#include "EventDispatcher.h"
#include "ClickManager.h"
#include "MouseClickEvent.h"
#include "Camera.h"
#include "TemplateBar.h"
#include "Grid.h"


using namespace std;

class MyGame : public Game{

public:
	MyGame();
	virtual ~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

private:

	vector<DisplayObject*> selectedImages;
	AnimatedSprite* character;
	AnimatedSprite* character1;
	Grid* dispGrid;
	Scene* allSprites;
	TemplateBar* templateBar;

	EventDispatcher* mouseDisp;
	MouseClickEvent* mouseClick;
	ClickManager* clickManager;

	Camera* camera;
	bool duplicatedLastFrame = true;
	bool noSpritesSelected = true;

};

#endif
