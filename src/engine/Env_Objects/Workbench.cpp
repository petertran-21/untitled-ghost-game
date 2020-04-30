#include <iostream>
#include <cstdlib>

#include "Workbench.h"

using namespace std;


Workbench::Workbench(DisplayObjectContainer* container) : MainEnvObj(){
    this->addAnimation("./resources/items/", "workbench", 1, 1, false);
	this->play("workbench");
    this->collisionContainer = container;
    container->addChild(this);
}
