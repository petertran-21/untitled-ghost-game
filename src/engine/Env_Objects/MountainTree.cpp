#include <iostream>
#include <cstdlib>

#include "MountainTree.h"

using namespace std;


MountainTree::MountainTree(DisplayObjectContainer* container) : MainEnvObj(){
    this->id = "MountainTree";
    this->addAnimation("./resources/items/", "mountain_tree", 1, 1, false);
    this->addAnimation("./resources/items/", "mountain_tree_dead", 1, 1, false);
	this->play("mountain_tree");
    this->collisionContainer = container;
    container->addChild(this);
}

void MountainTree::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainEnvObj::update(pressedKeys, currState);

    if (mined){
        this->play("mountain_tree_dead");
    }
}
