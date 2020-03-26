#include <iostream>
#include <cstdlib>
#include <math.h>

#include "Fire.h"

using namespace std;

Fire::Fire(SDL_Point pos) : AnimatedSprite("Fire"){
    this->position = pos;

    this->addAnimation("./resources/items/", "fire", 1, 1, false);
	this->play("fire");
}


void Fire::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    AnimatedSprite::update(pressedKeys, currState);
}
