#ifndef SHRUB_H
#define SHRUB_H

#include "Controller.h"
#include "MainEnvObj.h"

#include "Fire.h"
#include "Arrow.h"

using namespace std;

class Shrub : public MainEnvObj{
    
    public:
        Shrub(DisplayObjectContainer* container);

        void process_fire();
        void resolve_collision(DisplayObject *obj);
        int subtype = 11;

};

#endif