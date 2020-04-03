#include <iostream>
#include <cstdlib>
#include <math.h>

#include "Arrow.h"

using namespace std;


Arrow::Arrow() : MainNPCObj(){

    this->addAnimation("./resources/items/", "arrow", 1, 1, false);

	this->play("arrow");
}
Arrow::Arrow(SDL_Point pos, directions direction, DisplayObjectContainer* npcParent) : MainNPCObj(){
    this->position = pos;
    this->dir = direction;

    switch(dir){
        case N:
            position.y += 100;
            break;
        case S:
            position.x += 100;
            break;
        case W: 
            position.x += 100;
            position.y += 100;
            break;
    }

    this->addAnimation("./resources/items/", "arrow", 1, 1, false);
	this->play("arrow");
    this->parent = npcParent;
}

void Arrow::fly(){
    switch (dir){
        case N: 
            //check collision @ direction//
            rotation = -M_PI/2;
            position.y -= movespeed; 
            break;
        case S:
            //check collision @ direction//
            rotation = M_PI/2;
            position.y += movespeed; 
            break;
        case E: 
            //check collision @ direction//
            rotation = 0;
            position.x += movespeed; 
            break;
        case W: 
            //check collision @ direction//
            rotation = M_PI;
            position.x -= movespeed; 
            break;
        }

    //cout << position.x << endl;
    //cout << position.y << endl;
}

void Arrow::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    AnimatedSprite::update(pressedKeys, currState);
    Arrow::fly();
}
