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
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);

        bool flammable = false;
        bool on_fire = false;
        int fire_timer = 0;
        int fire_threshold = 10;  //how long it takes to catch fire, incremented in collision resolution
        int burn_time_max = 40;      //how long it takes to burn
        int burn_timer = 0;
        bool burned = false;
        void process_fire();
        
        void resolve_collision(DisplayObject *obj);
        void resolve_adjacency(DisplayObject *obj, int status);

};

#endif