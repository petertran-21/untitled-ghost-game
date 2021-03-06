#include <iostream>
#include <cstdlib>

#include "SwampTree.h"

using namespace std;


SwampTree::SwampTree(DisplayObjectContainer* container, DisplayObjectContainer* drawContainer) : MainEnvObj(){
    this->subtype = SWAMPTREE_SUBTYPE;
    this->addAnimation("./resources/items/", "swamptree", 1, 1, false);
    this->addAnimation("./resources/items/", "wood", 1, 1, false);
	this->play("swamptree");
    this->collisionContainer = container;
    container->addChild(this);
    this->drawingContainer = drawContainer;
}
