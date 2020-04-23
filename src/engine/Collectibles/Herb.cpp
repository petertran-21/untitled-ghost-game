#include <iostream>
#include <cstdlib>

#include "Herb.h"

using namespace std;

Herb::Herb(DisplayObjectContainer* container):MainCollectibles(){
    this->addAnimation("./resources/items/", "herb", 1, 1, false);
    this->play("herb");
    this->collisionContainer = container;
}

void Herb::resolve_collision(DisplayObject *obj){   

}