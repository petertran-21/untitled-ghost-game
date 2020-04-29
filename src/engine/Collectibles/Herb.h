#ifndef HERB_H
#define HERB_H
#define HERB_SUBTYPE 122

#include "Controller.h"
#include "MainCollectibles.h"
#include "DisplayObjectContainer.h"

using namespace std;

class Herb: public MainCollectibles{
    
    public:
        Herb(DisplayObjectContainer* container);
        void resolve_collision(DisplayObject *obj);

};

#endif