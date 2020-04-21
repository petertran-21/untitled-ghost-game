#include <iostream>
#include <cstdlib>

#include "Log.h"

using namespace std;


Log::Log(DisplayObjectContainer* container) : MainNPCObj(){
    this->addAnimation("./resources/items/", "tree", 1, 1, false);
    this->addAnimation("./resources/items/", "log", 1, 1, false);

	this->play("tree");
    this->subtype = LOG_SUBTYPE;

    this->collisionContainer = container;
    container->addChild(this);
}

void Log::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    AnimatedSprite::update(pressedKeys, currState);

    if (chopped) {
        this->play("log");
    }
}

void Log::resolve_collision(DisplayObject *obj){
    //on collide w/water --> sink
    /*
    if (obj->type == "Water"){
        sunk = true;
        cout << "SUNK" << endl;
    }
    */
}

void Log::resolve_adjacency(DisplayObject *obj, int status){
    if (obj->type == "NPC"){
        //push log around
        if (!sunk && chopped){
            switch(status){
                case 0: return; break;
                case 1: position.x -= 100; break;
                case 2: position.x += 100; break;
                case 3: position.y += 100; break;
                case 4: position.y -= 100; break;
            }
        }
    }
}