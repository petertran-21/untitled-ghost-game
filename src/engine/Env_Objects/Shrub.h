#ifndef SHRUB_H
#define SHRUB_H

#include "Controller.h"
#include "MainEnvObj.h"

#include "Fire.h"
#include "Arrow.h"

using namespace std;

class Shrub : public MainEnvObj{
    
    public:
        Shrub();

        void process_fire();
        void resolve_collision(DisplayObject *obj);

};

#endif