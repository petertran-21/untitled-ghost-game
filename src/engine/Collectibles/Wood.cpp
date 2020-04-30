#include <iostream>
#include <cstdlib>

#include "Wood.h"

using namespace std;

Wood::Wood(DisplayObjectContainer* container, DisplayObjectContainer* allSprites):MainCollectibles(){
    this->addAnimation("./resources/items/", "wood", 1, 1, false);
    this->play("wood");
    this->collisionContainer = container;
    container->addChild(this);
    this->subtype = WOOD_SUBTYPE;
    this->drawingContainer = allSprites;
}

void Wood::resolve_collision(DisplayObject *obj){   
    cout<<"HELLO FROM WOOD RESOLVE COLLLISION"<<endl;
}