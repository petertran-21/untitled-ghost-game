#include <iostream>
#include <cstdlib>

#include "Shrub.h"

using namespace std;


Shrub::Shrub() : MainEnvObj(){

    this->addAnimation("./resources/items/", "shrub", 1, 1, false);
    this->addAnimation("./resources/items/", "shrub_burned", 1, 1, false);
    this->flammable = true;
    this->fire_timer = 0;
    this->fire_threshold = 5;

	this->play("shrub");
}

void Shrub::process_fire(){
    this->play("shrub_burned");
}

void Shrub::resolve_collision(DisplayObject *obj){
    cout << "HELLO FROM RESOLVE SHRUB" << endl;
    Fire *f = dynamic_cast<Fire*>(obj);
    if (f){
        cout << "HIT BY FIRE!" << endl;
        if (burn_timer == burn_time_max){
            cout << "BURNED UP" << endl;
        }
    }

    Arrow *a = dynamic_cast<Arrow*>(obj);
    if (a) cout << "HIT BY ARROW!" << endl;
}