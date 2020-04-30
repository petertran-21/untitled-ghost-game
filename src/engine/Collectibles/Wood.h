#ifndef WOOD_H
#define WOOD_H
#define WOOD_SUBTYPE 126

#include "Controller.h"
#include "MainCollectibles.h"
#include "DisplayObjectContainer.h"

using namespace std;

class Wood: public MainCollectibles{
    
    public:
        Wood(DisplayObjectContainer* container, DisplayObjectContainer* allSprites);
        void resolve_collision(DisplayObject *obj);

};

#endif