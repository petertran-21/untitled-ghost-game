#ifndef SHRUB_H
#define SHRUB_H
#define SHRUB_SUBTYPE 11

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

};

#endif