#ifndef MYGAME_H
#define MYGAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "AnimatedSprite.h"
#include "Scene.h"

using namespace std;

class MyGame : public Game{
	
public:
	MyGame();
	virtual ~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	
private:

	Scene* scene_1;
	Scene* scene_2;

	bool using_scene_1;
};

#endif