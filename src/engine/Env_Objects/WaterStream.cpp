#include <iostream>
#include <cstdlib>

#include "WaterStream.h"
#include "MainNPC.h"
#include "Crab.h"

using namespace std;


WaterStream::WaterStream(directions dir, DisplayObjectContainer* container) : MainEnvObj(){
    this->dir = dir;
    this->addAnimation("./resources/items/", "water_stream", 1, 1, false);
	this->play("water_stream");
    this->collisionContainer = container;
    this->subtype = WATERSTREAM_SUBTYPE;
}


void WaterStream::resolve_collision(DisplayObject* obj){
    MainNPC* npc = dynamic_cast<MainNPC*>(obj);
    Crab* crab = dynamic_cast<Crab*>(obj);
    if (npc || crab){

        push_timer++;
        if (push_timer == push_time_max){
            push_timer = 0;
            switch(dir){
                case N: obj->position.y = position.y-100; break;
                case S: obj->position.y = position.y+100; break;
                case E: obj->position.x = position.x+100; break;
                case W: obj->position.x = position.x-100; break;
            }
        }
    }
    else push_timer = 0;
}