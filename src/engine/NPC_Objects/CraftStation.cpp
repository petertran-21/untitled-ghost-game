#include <iostream>
#include <cstdlib>
#include <math.h>

#include "CraftStation.h"

using namespace std;

CraftStation::CraftStation() : MainNPCObj(){
    this->subtype = 121;
    this->addAnimation("./resources/items/", "craftstation", 1, 1, false);
	this->play("craftstation");
}

void CraftStation::resolve_collision(DisplayObject *obj){

}