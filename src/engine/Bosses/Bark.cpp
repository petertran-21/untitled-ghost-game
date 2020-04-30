#include <iostream>
#include <cstdlib>
#include "Bark.h"
#include <math.h>

using namespace std;

Bark::Bark(int width, int height, int angle, DisplayObjectContainer* container, DisplayObjectContainer* allSprites) : MainNPCObj(){
    this->subtype = 109;
    this->id = "bark";

    this->position.x = width/2;
    this->position.y = height/2;
    this->rotation = angle;

	this->addAnimation("./resources/bosses/", "bark", 1, 1, false);

    this->play("bark");
    this->collisionContainer = container;
    container->addChild(this);
}

void Bark::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainNPCObj::update(pressedKeys, currState);
    position.x += cos(rotation) * movespeed;
    position.y += sin(rotation) * movespeed;
}

void Bark::resolve_collision(DisplayObject* obj){
    MainNPC * npc = dynamic_cast<MainNPC*>(obj);
    if (npc){
        npc->is_possessed = false;
    }
}