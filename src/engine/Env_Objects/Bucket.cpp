#include <iostream>
#include <cstdlib>

#include "Bucket.h"

using namespace std;


Bucket::Bucket(DisplayObjectContainer* container) : MainCollectibles(){
    this->id = "Bucket";
    this->addAnimation("./resources/items/", "bucket_empty", 1, 1, false);
    this->addAnimation("./resources/items/", "bucket_full", 1, 1, false);
	this->play("bucket_empty");
    this->collisionContainer = container;
    container->addChild(this);
    this->subtype = BUCKET_SUBTYPE;
}