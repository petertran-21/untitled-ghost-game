#ifndef CRAB_H
#define CRAB_H
#define CRAB_SUBTYPE 16

#include "Controller.h"
#include "MainNPCObj.h"

using namespace std;

class Crab : public MainNPCObj{
    
    public:

        Crab(DisplayObjectContainer* container);
        bool collected = false;
        int subtype = 16;
        void resolve_collision(DisplayObject *obj);
};
#endif