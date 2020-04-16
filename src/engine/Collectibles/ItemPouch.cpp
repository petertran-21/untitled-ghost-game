#include <iostream>
#include <cstdlib>

#include "ItemPouch.h"

using namespace std;

ItemPouch::ItemPouch(DisplayObjectContainer* container):MainCollectibles(){
    this->addAnimation("./resources/items/", "item_pouch", 1, 1, false);
    this->play("item_pouch");
    this->collisionContainer = container;
    container->addChild(this);
    this->subtype = ITEMPOUCH_SUBTYPE;
}

void ItemPouch::resolve_collision(DisplayObject *obj){   

}