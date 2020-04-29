#ifndef CRAFTSTATION_H
#define CRAFTSTATION_H
#define CRAFTSTATION_SUBTYPE 123

#include "Controller.h"
#include "MainNPCObj.h"

using namespace std;

class CraftStation : public MainNPCObj{
    
    public:

        CraftStation();

        void resolve_collision(DisplayObject *obj);
};
#endif
