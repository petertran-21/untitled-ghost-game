#include <iostream>
#include <cstdlib>
#include <math.h>

#include "Crab.h"

using namespace std;

Crab::Crab(DisplayObjectContainer* container) : MainNPCObj(){
    this->addAnimation("./resources/items/", "crab_idle", 1, 1, false);
	this->play("crab_idle");
    this->collisionContainer = container;
    container->addChild(this);
    this->subtype = CRAB_SUBTYPE;
}

void Crab::resolve_collision(DisplayObject *obj){

}