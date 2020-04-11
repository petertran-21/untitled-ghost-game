#include <iostream>
#include <cstdlib>

#include "Valve.h"

using namespace std;


Valve::Valve(DisplayObjectContainer* container) : MainEnvObj(){

    this->addAnimation("./resources/items/", "valve", 1, 1, false);
    
	this->play("valve");
    this->collisionContainer = container;
}

void Valve::toggle(){

    if (on) on = false;
    else on = true;

    for (WaterJet* w : jets){
        w->active = on;
        w->dir = this->dir;
    }
}

void Valve::add_jet(WaterJet* w){
    jets.push_back(w);
}

void Valve::resolve_collision(DisplayObject* obj){
    //do nothing

}