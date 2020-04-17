#ifndef VALVE_H
#define VALVE_H
#define VALVE_SUBTYPE 12

#include "Controller.h"
#include "MainEnvObj.h"
#include <vector>
#include "WaterJet.h"

using namespace std;

class Valve : public MainEnvObj{
    
    public:
        Valve(DisplayObjectContainer* container, directions dir);
        
        bool on = false;
        void toggle();
        vector<WaterJet*> jets;
        directions dir = S;
        int subtype = 12;

        void add_jet(WaterJet* w);
        void resolve_collision(DisplayObject *obj);

};

#endif