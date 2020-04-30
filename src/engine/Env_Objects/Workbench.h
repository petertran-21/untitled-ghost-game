#ifndef WORKBENCH_H
#define WORKBENCH_H
#define WORKBENCH_SUBTYPE 303

#include "Controller.h"
#include "MainEnvObj.h"


using namespace std;

class Workbench : public MainEnvObj{
    
    public:
        Workbench(DisplayObjectContainer* container);

};

#endif