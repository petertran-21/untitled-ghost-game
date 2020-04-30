#ifndef BOAT_H
#define BOAT_H
#define BOAT_SUBTYPE 121

#include "Controller.h"
#include "MainNPCObj.h"

using namespace std;

class Boat : public MainNPCObj{
    
    public:

        Boat(DisplayObjectContainer* container);

        void resolve_collision(DisplayObject *obj);
};
#endif
