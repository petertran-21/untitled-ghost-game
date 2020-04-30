#ifndef SWAMPTREE_H
#define SWAMPTREE_H
#define SWAMPTREE_SUBTYPE 125

#include "Controller.h"
#include "MainEnvObj.h"


using namespace std;

class SwampTree : public MainEnvObj{
    
    public:
        SwampTree(DisplayObjectContainer* container, DisplayObjectContainer* drawContainer);

        bool mined = false;
        
        DisplayObjectContainer* drawingContainer;
        DisplayObjectContainer* collisionContainer;

};

#endif