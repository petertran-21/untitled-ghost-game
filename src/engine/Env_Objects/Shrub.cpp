#include <iostream>
#include <cstdlib>

#include "Shrub.h"

using namespace std;


Shrub::Shrub(DisplayObjectContainer* container) : MainEnvObj(){
    this->addAnimation("./resources/items/", "shrub", 1, 1, false);
    this->addAnimation("./resources/items/", "shrub_burned", 1, 1, false);
    this->flammable = true;
    this->fire_timer = 0;
    this->fire_threshold = 5;
    this->subtype = SHRUB_SUBTYPE;
	this->play("shrub");
    this->collisionContainer = container;
    container->addChild(this);
}

void Shrub::process_fire(){
    this->play("shrub_burned");
}

void Shrub::resolve_collision(DisplayObject *obj){
    Fire *f = dynamic_cast<Fire*>(obj);
    if (f){
        if (burn_timer == burn_time_max){
            vector<DisplayObject*>::iterator fireItr = find(this->collisionContainer->children.begin(), this->collisionContainer->children.end(), obj);
            if (fireItr != this->collisionContainer->children.end()){

                DisplayObjectContainer* npc = f->parent;
                npc->removeImmediateChild(npc->children.at(0));
                
                this->collisionContainer->children.erase(fireItr);
            }
        }
    }

    Arrow *a = dynamic_cast<Arrow*>(obj);
    if (a) cout << "HIT BY ARROW!" << endl;
    
}