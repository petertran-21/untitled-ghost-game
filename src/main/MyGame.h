#ifndef MYGAME_H
#define MYGAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "AnimatedSprite.h"
#include "Scene.h"
#include "Sound.h"
#include "Camera.h"

using namespace std;

class MyGame : public Game{
	
public:
	MyGame();
	virtual ~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	
private:

	Camera* camera;
	Sound* sound_manager;
	Scene* scene_1;
	Scene* scene_2;

	DisplayObjectContainer* main_character;

	bool using_scene_1;
};

#endif