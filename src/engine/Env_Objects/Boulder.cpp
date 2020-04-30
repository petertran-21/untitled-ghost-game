#include <iostream>
#include <cstdlib>

#include "Boulder.h"
#include "NPCStrongman.h"

using namespace std;


Boulder::Boulder(DisplayObjectContainer* container) : MainEnvObj(){
    this->addAnimation("./resources/items/", "boulder", 1, 1, false);
	this->play("boulder");
    this->collisionContainer = container;
    container->addChild(this);
}

void Boulder::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainEnvObj::update(pressedKeys, currState);
}

void Boulder::resolve_adjacency(DisplayObject* obj, int status){
    NPCStrongman *s = dynamic_cast<NPCStrongman*>(obj);
    if (s && s->strongmode){
        //push boulder
        switch(status){
            case 0: return; break;
            case 1: position.x -= 100; break;
            case 2: position.x += 100; break;
            case 3: position.y += 100; break;
            case 4: position.y -= 100; break;
        }
    }
}