#ifndef MYGAME_H
#define MYGAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "AnimatedSprite.h"
#include "EventDispatcher.h"
#include "QuestManager.h"
#include "PickedUpEvent.h"
#include "Scene.h"
#include "Sound.h"
#include "Camera.h"
#include "Tween.h"
#include "Layer.h"
#include "TweenJuggler.h"

using namespace std;

class MyGame : public Game{
	
public:
	MyGame();
	virtual ~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

private:

	AnimatedSprite* sun;
	Sprite* planet1;
	Sprite* planet2;
	Sprite* moon1_1;

	Camera* camera;
	Sound* sound_manager;
	Scene* scene_1;
	Scene* scene_2;

	AnimatedSprite* main_character;
	Layer* background;
	Layer* midground;
	Layer* foreground;

	TweenJuggler* tweenHandler;
	Tween* characterFadeIn;

	bool using_scene_1;
};

#endif
