#ifndef SWAMPBRIDGE_H
#define SWAMPBRIDGE_H
#define SWAMPBRIDGE_SUBTYPE 127

#include "Controller.h"
#include "MainNPCObj.h"


using namespace std;

class SwampBridge : public MainNPCObj{
    
    public:
        SwampBridge(DisplayObjectContainer* container, bool built);
        bool cancross;

};

#endif