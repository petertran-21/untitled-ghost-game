#include <iostream>
#include <cstdlib>
#include <math.h>

#include "Fire.h"

using namespace std;

Fire::Fire(SDL_Point pos, DisplayObjectContainer* npcParent) : MainNPCObj(){
    this->position = pos;

    this->addAnimation("./resources/items/", "fire", 1, 1, false);
	this->play("fire");
    this->parent = npcParent;
}

void Fire::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    AnimatedSprite::update(pressedKeys, currState);
}

void Fire::resolve_collision(DisplayObject* obj){
    Shrub *s = dynamic_cast<Shrub*>(obj);
    if (s){
        if (s->fire_timer < s->fire_threshold) s->fire_timer++;
    }
}