#include <iostream>
#include <cstdlib>

#include "CaveLake.h"

using namespace std;


CaveLake::CaveLake(DisplayObjectContainer* container) : MainEnvObj(){
    this->id = "CaveLake";
    this->addAnimation("./resources/items/", "cavelake", 1, 1, false);
    this->addAnimation("./resources/items/", "cavelake_mined", 1, 1, false);
	this->play("cavelake");
    this->subtype = CAVELAKE_SUBTYPE;

    this->collisionContainer = container;
    container->addChild(this);
}

void CaveLake::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainEnvObj::update(pressedKeys, currState);

    if (mined){
        this->play("cavelake_mined");
    }
}
