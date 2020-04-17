#ifndef GEMHOLDER_H
#define GEMHOLDER_H

#include "Controller.h"
#include "MainNPCObj.h"

using namespace std;

class GemHolder : public MainNPCObj{
    
    public:

        GemHolder();

        void resolve_collision(DisplayObject *obj);
};
#endif
