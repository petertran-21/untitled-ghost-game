#include <iostream>
#include <cstdlib>

#include "Door.h"

using namespace std;


Door::Door(DisplayObjectContainer* container) : MainEnvObj(){
    this->subtype = 105;
    this->addAnimation("./resources/items/", "door", 1, 1, false);

	this->play("door");
    this->collisionContainer = container;
}

void Door::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainEnvObj::update(pressedKeys, currState);
}

void Door::resolve_collision(DisplayObject *obj){
}