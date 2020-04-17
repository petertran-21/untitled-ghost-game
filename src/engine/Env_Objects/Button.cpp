#include <iostream>
#include <cstdlib>

#include "Button.h"

using namespace std;


Button::Button(DisplayObjectContainer* container) : MainEnvObj(){
    this->subtype = 104;
    this->addAnimation("./resources/items/", "button_unpressed", 1, 1, false);

	this->play("button_unpressed");
    this->collisionContainer = container;
}

void Button::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainEnvObj::update(pressedKeys, currState);
}

void Button::resolve_collision(DisplayObject *obj){
}