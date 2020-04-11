#ifndef CRAB_H
#define CRAB_H

#include "Controller.h"
#include "MainNPCObj.h"

using namespace std;

class Crab : public MainNPCObj{
    
    public:

        Crab();
        bool collected = false;

        void resolve_collision(DisplayObject *obj);
};
#endif