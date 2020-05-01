#include <iostream>
#include <cstdlib>

#include "Herb.h"

using namespace std;

Herb::Herb(DisplayObjectContainer* container):MainCollectibles(){
    this->addAnimation("./resources/items/", "herb", 1, 1, false);
    this->play("herb");
    this->id = "Herb";
    this->collisionContainer = container;
    container->addChild(this);
    this->subtype = HERB_SUBTYPE;
}

void Herb::resolve_collision(DisplayObject *obj){   
    // cout<<"HELLO FROM HERB RESOLVE COLLLISION"<<endl;
}