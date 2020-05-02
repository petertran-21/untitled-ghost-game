#include <iostream>
#include <cstdlib>

#include "SceneTrigger.h"

using namespace std;


SceneTrigger::SceneTrigger(DisplayObjectContainer *container, string scene_path) : AnimatedSprite(){
    this->type = "SceneTrigger";
    this->id = "SceneTrigger";
    this->addAnimation("./resources/items/", "scene_trigger", 1, 1, false);
	this->play("scene_trigger");
    this->collisionContainer = container;
    this->ghost_pos = { -5000, -5000 };
    this->scene_path = scene_path;
}

void SceneTrigger::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
	AnimatedSprite::update(pressedKeys, currState);
}

void SceneTrigger::resolve_collision(DisplayObject* obj){
    active = false;
}