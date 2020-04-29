#include <iostream>
#include <cstdlib>
#include <math.h>

#include "Boat.h"

using namespace std;

Boat::Boat(DisplayObjectContainer* container) : MainNPCObj(){
    this->subtype = BOAT_SUBTYPE;
    this->addAnimation("./resources/items/", "boat", 1, 1, false);
	this->play("boat");
    this->collisionContainer = container;
    container->addChild(this);
    this->subtype = BOAT_SUBTYPE;
}

void Boat::resolve_collision(DisplayObject *obj){

}