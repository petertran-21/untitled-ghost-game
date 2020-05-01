#include <iostream>
#include <cstdlib>

#include "FallenTree.h"

using namespace std;


FallenTree::FallenTree(DisplayObjectContainer* container) : MainEnvObj(){
    this->addAnimation("./resources/items/", "fallenTree", 1, 1, false, "notdestroyed");
    this->addAnimation("./resources/items/", "fallenTree_destroyed", 1, 1, false, "destroyed");

	this->play("notdestroyed");
    this->collisionContainer = container;
    container->addChild(this);

}

void FallenTree::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainEnvObj::update(pressedKeys, currState);

    if (destroyed){
        this->play("destroyed");
    }
}
