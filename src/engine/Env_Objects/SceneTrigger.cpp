#include <iostream>
#include <cstdlib>

#include "SceneTrigger.h"

using namespace std;


SceneTrigger::SceneTrigger(DisplayObjectContainer *container) : AnimatedSprite(){
    this->type = "SceneTrigger";
    this->id = "SceneTrigger";
    this->addAnimation("./resources/items/", "scene_trigger", 1, 1, false);
	this->play("scene_trigger");
    this->collisionContainer = container;

    this->scene_path = "./resources/scenes/beachRoom2.json";
}

void SceneTrigger::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
	AnimatedSprite::update(pressedKeys, currState);
}

void SceneTrigger::resolve_collision(DisplayObject* obj){
    active = false;
}