#include <iostream>
#include <cstdlib>
#include <math.h>

#include "Arrow.h"

using namespace std;


Arrow::Arrow(SDL_Point pos, directions direction, DisplayObjectContainer* container, DisplayObjectContainer* allSprites) : MainNPCObj(){
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
    this->collisionContainer = container;
    container->addChild(this);
    this->drawingContainer = allSprites;
    drawingContainer->addChild(this);
}

void Arrow::fly(){
    switch (dir){
        case N: 
            //check collision @ direction//
            rotation = -M_PI/2;
            position.y -= movespeed; 
            //if (col_arrow) col_arrow->position.y -= movespeed;
            break;
        case S:
            //check collision @ direction//
            rotation = M_PI/2;
            position.y += movespeed; 
            //if (col_arrow) col_arrow->position.y += movespeed;
            break;
        case E: 
            //check collision @ direction//
            rotation = 0;
            position.x += movespeed; 
            //if (col_arrow) col_arrow->position.x += movespeed;
            break;
        case W: 
            //check collision @ direction//
            rotation = M_PI;
            position.x -= movespeed; 
            //if (col_arrow) col_arrow->position.x -= movespeed;
            break;
        }

    //cout << position.x << endl;
    //cout << position.y << endl;
}

void Arrow::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    AnimatedSprite::update(pressedKeys, currState);
    Arrow::fly();
}

void Arrow::resolve_collision(DisplayObject *obj){
    //destroy self on hit: bridge, shrub, 
    if (obj->getSubtype()==101 || obj->getSubtype()==11){
        vector<DisplayObject*>::iterator arrowItr = find(collisionContainer->children.begin(), collisionContainer->children.end(), this);
        if (arrowItr != collisionContainer->children.end()){            
            collisionContainer->children.erase(arrowItr);
        }
    }
}