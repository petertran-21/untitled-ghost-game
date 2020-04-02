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

void Shrub::resolve_collision(DisplayObject *obj){
    Fire *f = dynamic_cast<Fire*>(obj);
    if (f) cout << "HIT BY FIRE!" << endl;

    Arrow *a = dynamic_cast<Arrow*>(obj);
    if (a) cout << "HIT BY ARROW!" << endl;
}