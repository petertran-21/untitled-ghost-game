#include <iostream>
#include <cstdlib>

#include "ItemPouch.h"

using namespace std;

ItemPouch::ItemPouch(DisplayObjectContainer* container):MainCollectibles(){
    this->subtype = "item pouch";
    this->addAnimation("./resources/items/", "item_pouch", 1, 1, false);
    this->play("item_pouch");
    this->collisionContainer = container;
}

void ItemPouch::resolve_collision(DisplayObject *obj){   

}