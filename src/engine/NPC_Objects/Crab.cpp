#include <iostream>
#include <cstdlib>
#include <math.h>

#include "Crab.h"

using namespace std;

Crab::Crab() : MainNPCObj(){
    this->addAnimation("./resources/items/", "crab_idle", 1, 1, false);
	this->play("crab_idle");
}

void Crab::resolve_collision(DisplayObject *obj){

}