#ifndef WATER_STREAM_H
#define WATER_STREAM_H

#include "Controller.h"
#include "MainEnvObj.h"


using namespace std;

class WaterStream : public MainEnvObj{
    
    public:
        WaterStream(directions dir, DisplayObjectContainer* container);
        directions dir = None;

        int push_timer = 0;
        int push_time_max = 10;

        void resolve_collision(DisplayObject *obj);

};

#endif