#include <iostream>
#include <cstdlib>

#include "Shrub.h"

using namespace std;


Shrub::Shrub(DisplayObjectContainer* container) : MainEnvObj(){
    this->addAnimation("./resources/items/", "shrub", 1, 1, false);
    this->addAnimation("./resources/items/", "shrub_fire", 1, 1, false);
    this->addAnimation("./resources/items/", "shrub_burned", 1, 1, false);
    this->flammable = true;
    this->fire_timer = 0;
    this->fire_threshold = 5;
    this->subtype = SHRUB_SUBTYPE;
	this->play("shrub");
    this->collisionContainer = container;
    container->addChild(this);
}

void Shrub::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainEnvObj::update(pressedKeys, currState);

    if (flammable){
        //catching fire
        if (fire_timer == fire_threshold){
            on_fire = true;
            fire_timer++;
        }

        //burning
        if (on_fire){

            burn_timer++;
            this->play("shrub_fire");
            //burned
            if (burn_timer == burn_time_max){
                process_fire();
            }
        }
    }
}

void Shrub::process_fire(){
    on_fire = false;
    burned = true;
    this->play("shrub_burned");
}

void Shrub::resolve_collision(DisplayObject *obj){
    Fire *f = dynamic_cast<Fire*>(obj);
    if (f){
        if (fire_timer < fire_threshold) fire_timer++;
        else if (burn_timer == burn_time_max){
            vector<DisplayObject*>::iterator fireItr = find(this->collisionContainer->children.begin(), this->collisionContainer->children.end(), obj);
            if (fireItr != this->collisionContainer->children.end()){

                DisplayObjectContainer* npc = f->parent;
                npc->removeImmediateChild(npc->children.at(0));
                
                this->collisionContainer->children.erase(fireItr);
            }
        }
    }
    
}

void Shrub::resolve_adjacency(DisplayObject *obj, int status){
    Shrub *s = dynamic_cast<Shrub*>(obj);
    if (s && on_fire && status != 0){
        if (s->on_fire == false && !s->burned) s->on_fire = true;
    }
}