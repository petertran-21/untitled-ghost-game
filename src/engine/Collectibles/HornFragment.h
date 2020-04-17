#ifndef HORNFRAGMENT_H
#define HORNFRAGMENT_H

#include "Controller.h"
#include "MainCollectibles.h"
#include "DisplayObjectContainer.h"

using namespace std;

class HornFragment : public MainCollectibles{
    
    public:
        HornFragment(DisplayObjectContainer* container);

        void resolve_collision(DisplayObject *obj);

};

#endif