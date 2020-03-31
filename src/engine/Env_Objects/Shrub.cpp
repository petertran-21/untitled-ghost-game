#include <iostream>
#include <cstdlib>

#include "Shrub.h"

using namespace std;


Shrub::Shrub() : MainEnvObj(){

    this->type = "Shrub";
    this->addAnimation("./resources/items/", "shrub", 1, 1, false);
    this->addAnimation("./resources/items/", "shrub_burned", 1, 1, false);
    this->flammable = true;

	this->play("shrub");
}

void Shrub::process_fire(){
    this->play("shrub_burned");
}