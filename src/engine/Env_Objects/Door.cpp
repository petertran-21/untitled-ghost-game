#include <iostream>
#include <cstdlib>

#include "Door.h"

using namespace std;


Door::Door(DisplayObjectContainer* container, DisplayObjectContainer* drawContainer) : MainEnvObj(){
    this->subtype = 105;
    this->addAnimation("./resources/items/", "door", 1, 1, false, "door_open");
    this->addAnimation("./resources/items/", "pit", 1, 1, false, "door_closed");
	this->play("door_closed");
    this->collisionContainer = container;
    this->drawingContainer = drawContainer;
    drawContainer->addChild(this);
    container->addChild(this);
}

void Door::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainEnvObj::update(pressedKeys, currState);
    if (open){ //when button is pressed
        this->play("door_open");
        this->type = ""; //type deteremines the collision resolution for EnvObj
    }
    else{
        this->play("door_closed");
        this->type = "EnvObj";
    }

}

void Door::resolve_collision(DisplayObject *obj){
    //do nothing
}