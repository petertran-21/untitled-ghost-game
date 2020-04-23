#include <iostream>
#include <cstdlib>

#include "PoisonGas.h"

using namespace std;


PoisonGas::PoisonGas(DisplayObjectContainer* container) : MainEnvObj(){
    this->subtype = 120;
    //TO DO: Change out with translucent green image
    this->addAnimation("./resources/items/", "rock", 1, 1, false);

	this->play("rock");
    this->collisionContainer = container;
}

void PoisonGas::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainEnvObj::update(pressedKeys, currState);
}

void PoisonGas::resolve_collision(DisplayObject *obj){
}