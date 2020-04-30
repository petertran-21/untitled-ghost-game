#include <iostream>
#include <cstdlib>

#include "SwampBridge.h"

using namespace std;


SwampBridge::SwampBridge(DisplayObjectContainer* container) : MainEnvObj(){
    // this->addAnimation("./resources/items/", "swampbridge", 1, 1, false);
	// this->play("swampbridge");
    this->collisionContainer = container;
    container->addChild(this);
}
