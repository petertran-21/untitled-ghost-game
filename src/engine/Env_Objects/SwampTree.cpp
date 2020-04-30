#include <iostream>
#include <cstdlib>

#include "SwampTree.h"

using namespace std;


SwampTree::SwampTree(DisplayObjectContainer* container, DisplayObjectContainer* drawContainer) : MainEnvObj(){
    this->subtype = SWAMPTREE_SUBTYPE;
    this->addAnimation("./resources/items/", "swamptree", 1, 1, false);
	this->play("swamptree");
    this->collisionContainer = container;
    container->addChild(this);
    this->drawingContainer = drawContainer;
}

void SwampTree::resolve_collision(DisplayObject *obj){
    cout<<"HELLO from SWAMPTREE RESOLVE"<<endl;
}