#include <iostream>
#include <cstdlib>

#include "BreakableWall.h"

using namespace std;


BreakableWall::BreakableWall(DisplayObjectContainer* container) : MainEnvObj(){
    this->addAnimation("./resources/items/", "breakable_wall", 1, 1, false);
    
	this->play("breakable_wall");
    this->collisionContainer = container;
}

void BreakableWall::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainEnvObj::update(pressedKeys, currState);

    if (broken){
        //REPLACE THIS WITH DELETE
        position.x = -100;
        position.y = -100;
    }
}

void BreakableWall::resolve_collision(DisplayObject* obj){
    //do nothing
}