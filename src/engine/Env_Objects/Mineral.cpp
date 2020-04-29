#include <iostream>
#include <cstdlib>

#include "Mineral.h"

using namespace std;


Mineral::Mineral(DisplayObjectContainer* container) : MainEnvObj(){
    this->id = "Mineral";
    this->addAnimation("./resources/items/", "mineral", 1, 1, false);
    this->addAnimation("./resources/items/", "mineral_mined", 1, 1, false);
	this->play("mineral");
    this->collisionContainer = container;
    container->addChild(this);
}

void Mineral::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainEnvObj::update(pressedKeys, currState);

    if (mined){
        this->play("mineral_mined");
    }
}
