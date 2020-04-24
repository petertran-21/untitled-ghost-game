#include <iostream>
#include <cstdlib>

#include "FireStream.h"
#include "MainNPC.h"

using namespace std;


FireStream::FireStream(directions dir, DisplayObjectContainer* container) : MainEnvObj(){
    this->dir = dir;
    this->addAnimation("./resources/bosses/", "fire_stream", 1, 1, false);
	this->play("fire_stream");
    this->collisionContainer = container;
    this->subtype = FIRESTREAM_SUBTYPE;
}
