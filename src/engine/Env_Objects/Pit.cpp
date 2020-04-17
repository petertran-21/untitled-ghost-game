#include <iostream>
#include <cstdlib>

#include "Pit.h"

using namespace std;


Pit::Pit(DisplayObjectContainer* container) : MainEnvObj(){
    this->subtype = "pit";
    this->addAnimation("./resources/items/", "pit", 1, 1, false);

	this->play("pit");
    this->collisionContainer = container;
}

void Pit::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainEnvObj::update(pressedKeys, currState);
}

void Pit::resolve_collision(DisplayObject *obj){
}