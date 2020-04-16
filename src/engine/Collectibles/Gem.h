#ifndef GEM_H
#define GEM_H

#include "Controller.h"
#include "MainCollectibles.h"
#include "DisplayObjectContainer.h"

using namespace std;

class Gem : public MainCollectibles{
    
    public:
        Gem(DisplayObjectContainer* container);

        void resolve_collision(DisplayObject *obj);

};

#endif