#ifndef CRAB_H
#define CRAB_H

#include "Controller.h"
#include "MainNPCObj.h"

using namespace std;

class GemHolder : public MainNPCObj{
    
    public:

        GemHolder();

        void resolve_collision(DisplayObject *obj);
};
#endif