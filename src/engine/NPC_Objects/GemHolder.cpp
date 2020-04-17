#include <iostream>
#include <cstdlib>
#include <math.h>

#include "GemHolder.h"

using namespace std;

GemHolder::GemHolder() : MainNPCObj(){
    this->subtype = "gem holder";
    this->addAnimation("./resources/items/", "gemholder", 1, 1, false);
	this->play("gemholder");
}

void GemHolder::resolve_collision(DisplayObject *obj){

}