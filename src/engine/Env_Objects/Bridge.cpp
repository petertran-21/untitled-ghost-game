#include <iostream>
#include <cstdlib>

#include "Bridge.h"

using namespace std;


Bridge::Bridge(DisplayObjectContainer* container) : MainEnvObj(){
    this->addAnimation("./resources/items/", "bridge_open", 1, 1, false);
    this->addAnimation("./resources/items/", "bridge_closed", 1, 1, false);

	this->play("bridge_closed");
    this->collisionContainer = container;
    container->addChild(this);
}

void Bridge::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainEnvObj::update(pressedKeys, currState);

    if (open){
        this->play("bridge_open");
    }
}

void Bridge::resolve_collision(DisplayObject *obj){
    Fire *f = dynamic_cast<Fire*>(obj);
    if (f){
        vector<DisplayObject*>::iterator fireItr = find(this->collisionContainer->children.begin(), this->collisionContainer->children.end(), obj);
        if (fireItr != this->collisionContainer->children.end()){

            DisplayObjectContainer* npc = f->parent;
            npc->removeImmediateChild(npc->children.at(0));
            
            this->collisionContainer->children.erase(fireItr);
        }
        open = true;
    }

    Arrow *a = dynamic_cast<Arrow*>(obj);
    if (a){
        open = true;
    }
    
}