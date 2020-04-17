#include <iostream>
#include <cstdlib>

#include "Rock.h"

using namespace std;


Rock::Rock(DisplayObjectContainer* container) : MainEnvObj(){
    this->subtype = 107;
    this->addAnimation("./resources/items/", "rock", 1, 1, false);

	this->play("rock");
    this->collisionContainer = container;
}

void Rock::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainEnvObj::update(pressedKeys, currState);
}

void Rock::resolve_collision(DisplayObject *obj){
}