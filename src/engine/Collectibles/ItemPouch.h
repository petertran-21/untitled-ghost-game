#ifndef ITEMPOUCH_H
#define ITEMPOUCH_H

#include "Controller.h"
#include "MainCollectibles.h"
#include "DisplayObjectContainer.h"

using namespace std;

class ItemPouch : public MainCollectibles{
    
    public:
        ItemPouch(DisplayObjectContainer* container);

        void resolve_collision(DisplayObject *obj);

};

#endif