#include <iostream>
#include <cstdlib>
#include "Bark.h"
#include <math.h>

using namespace std;

Bark::Bark(SDL_Point pos, int angle, DisplayObjectContainer* container, DisplayObjectContainer* allSprites) : MainNPCObj(){
    this->subtype = 109;
    this->id = "bark";

    this->position = pos;
    this->rotation = angle;

	this->addAnimation("./resources/bosses/", "bark", 1, 1, false);

    this->play("bark");
    this->collisionContainer = container;
    container->addChild(this);
    this->drawingContainer = allSprites;
    drawingContainer->addChild(this);
}

void Bark::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    AnimatedSprite::update(pressedKeys, currState);
    position.x = cos(rotation) * movespeed;
    position.y = sin(rotation) * movespeed;
}