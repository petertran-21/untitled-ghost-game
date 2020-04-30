#include <iostream>
#include <cstdlib>

#include "SwampBridge.h"

using namespace std;


SwampBridge::SwampBridge(DisplayObjectContainer* container, bool built) : MainNPCObj(){
    this->addAnimation("./resources/items/", "bridgeHorizontal", 1, 1, false, "built");
    this->addAnimation("./resources/items/", "swampwater", 1, 1, false, "notbuilt");
    if (built == true){
        this->play("built");
        this->cancross = true;
    }
    else{
        this->play("notbuilt");
        this->cancross = false;
    }
    this->collisionContainer = container;
    container->addChild(this);
}
