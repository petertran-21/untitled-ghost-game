#include <iostream>
#include <cstdlib>

#include "Gem.h"

using namespace std;

Gem::Gem(DisplayObjectContainer* container):MainCollectibles(){
    this->type = "Collectible";
    this->addAnimation("./resources/items/", "gem", 1, 1, false);
    this->play("gem");
    this->collisionContainer = container;
    container->addChild(this);
}
