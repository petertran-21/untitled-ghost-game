#include <iostream>
#include <cstdlib>

#include "CaveLake.h"

using namespace std;


CaveLake::CaveLake(DisplayObjectContainer* container) : Mineral(container){
    this->addAnimation("./resources/items/", "cavelake", 1, 1, false);
    this->addAnimation("./resources/items/", "cavelake_mined", 1, 1, false);
	this->play("cavelake");
}

void CaveLake::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainEnvObj::update(pressedKeys, currState);

    if (mined){
        this->play("cavelake_mined");
    }
}
