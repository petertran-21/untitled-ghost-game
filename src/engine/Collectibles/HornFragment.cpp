#include <iostream>
#include <cstdlib>

#include "HornFragment.h"

using namespace std;

HornFragment::HornFragment(DisplayObjectContainer* container):MainCollectibles(){
    this->addAnimation("./resources/items/", "horn_fragment", 1, 1, false);
    this->play("horn_fragment");
    this->collisionContainer = container;
}

void HornFragment::resolve_collision(DisplayObject *obj){   

}