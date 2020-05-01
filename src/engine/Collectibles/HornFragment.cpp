#include <iostream>
#include <cstdlib>

#include "HornFragment.h"

using namespace std;

HornFragment::HornFragment(DisplayObjectContainer* container):MainCollectibles(){
    this->type = "Collectible";
    this->id = "HornFragment";
    this->addAnimation("./resources/items/", "horn_fragment", 1, 1, false);
    this->play("horn_fragment");
    this->collisionContainer = container;
    container->addChild(this);
}
