#ifndef SWAMPTREE_H
#define SWAMPTREE_H
#define SWAMPTREE_SUBTYPE 125

#include "Controller.h"
#include "MainEnvObj.h"


using namespace std;

class SwampTree : public MainEnvObj{
    
    public:
        SwampTree(DisplayObjectContainer* container, DisplayObjectContainer* drawContainer);
        void resolve_collision(DisplayObject *obj);
        
        DisplayObjectContainer* drawingContainer;
        DisplayObjectContainer* collisionContainer;

};

#endif