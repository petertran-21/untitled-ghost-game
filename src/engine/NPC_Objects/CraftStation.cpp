#include <iostream>
#include <cstdlib>
#include <math.h>

#include "CraftStation.h"

using namespace std;

CraftStation::CraftStation(DisplayObjectContainer* container) : MainNPCObj(){
    this->subtype = CRAFTSTATION_SUBTYPE;
    this->addAnimation("./resources/items/", "craftstation", 1, 1, false);
	this->play("craftstation");

    this->collisionContainer = container;
    container->addChild(this);
}

void CraftStation::resolve_collision(DisplayObject *obj){

}