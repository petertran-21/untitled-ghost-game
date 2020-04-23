#include <iostream>
#include <cstdlib>
#include <math.h>

#include "Crab.h"

using namespace std;

Crab::Crab(DisplayObjectContainer* container, int initial_pos_x, int initial_pos_y) : MainNPCObj(){
    this->addAnimation("./resources/items/", "crab_idle", 1, 1, false);
	this->play("crab_idle");
    this->collisionContainer = container;
    container->addChild(this);
    this->targetLoc.x = initial_pos_x;
    this->targetLoc.y = initial_pos_y;

    this->subtype = CRAB_SUBTYPE;
}

void Crab::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainNPCObj::update(pressedKeys, currState);

    if (touching_button){
        //start the timer
        crab_timer++;
        walk();
        //reset timer and put crab at it's original location if timer maxed
        if (crab_timer >= crab_time_max && (this->position.x == this->targetLoc.x) && (this->position.y == this->targetLoc.y)){
            touching_button = false;
            crab_timer = 0;
        }
    }
}
void Crab::walk(){
    if ((crab_timer % walk_speed == 0) && (this->position.x != this->targetLoc.x) && (this->position.y != this->targetLoc.y)){
        if (this->position.x > 0){
            if (this->targetLoc.x > this->position.x){
                this->position.x += 100;
            }
            else if (this->targetLoc.x < this->position.x){
                this->position.x -= 100;
            }
        }
        else{
            if (this->targetLoc.x > this->position.x){
                this->position.x -= 100;
            }
            else if (this->targetLoc.x < this->position.x){
                this->position.x += 100;
            }
        }
        if (this->position.y > 0){
            if (this->targetLoc.y > this->position.y){
                this->position.y += 100;
            }
            else if (this->targetLoc.y < this->position.y){
                this->position.y -= 100;
            }
        }
        else{
            if (this->targetLoc.y > this->position.y){
                this->position.y -= 100;
            }
            else if (this->targetLoc.y < this->position.y){
                this->position.y += 100;
            }
        }
    }
}



void Crab::resolve_collision(DisplayObject *obj){
    // cout<<"Locations: "<<this->position.x<<"vs"<< (obj->position.x) <<" "<< this->position.y << "vs"<<(obj->position.y)<<" "<<(this->collected==false)<<endl;
    if (obj->getSubtype()==104 && (obj->position.x == this->position.x) && (obj->position.y == this->position.y)){
        if (this->collected==false){
            touching_button = true;
            Button* button = (Button*) obj;
            button->pressed = true;
        }
    }

}