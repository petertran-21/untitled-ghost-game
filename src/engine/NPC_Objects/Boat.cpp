#include <iostream>
#include <cstdlib>
#include <math.h>

#include "Boat.h"

using namespace std;

Boat::Boat() : MainNPCObj(){
    this->subtype = 121;
    this->addAnimation("./resources/items/", "boat", 1, 1, false);
	this->play("boat");
}

void Boat::resolve_collision(DisplayObject *obj){

}