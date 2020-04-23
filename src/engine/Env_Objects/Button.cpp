#include <iostream>
#include <cstdlib>

#include "Button.h"

using namespace std;


Button::Button(DisplayObjectContainer* container) : MainEnvObj(){
    this->subtype = BUTTON_SUBTYPE;

    this->addAnimation("./resources/items/", "button_unpressed", 1, 1, false);
    this->addAnimation("./resources/items/", "button_pressed", 1, 1, false);

	this->play("button_unpressed");
    this->collisionContainer = container;
    container->addChild(this);
}

void Button::add_door(Door* d){
    doors.push_back(d);
}

void Button::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainEnvObj::update(pressedKeys, currState);
    this->play("button_unpressed");
}

void Button::resolve_collision(DisplayObject *obj){
    if (obj->getSubtype() == 16 && (pressed == true) && (obj->position.x == this->position.x) && (obj->position.x == this->position.x)){
        this->play("button_pressed");
        cout<<"PRESSED BUTTON: "<<this->children.size()<<endl;
        for (DisplayObject* obj: this->children){
            Door* door = (Door*) obj;
            door->open = true;
        }
    }
    else{
        this->play("button_unpressed");
        for (DisplayObject* obj: this->children){
            Door* door = (Door*) obj;
            door->open = false;
        }
    }
    // cout<<<<endl;
}