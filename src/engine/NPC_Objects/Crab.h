#ifndef CRAB_H
#define CRAB_H
#define CRAB_SUBTYPE 16

#include "Controller.h"
#include "MainNPCObj.h"
#include "Button.h"

using namespace std;

class Crab : public MainNPCObj{
    
    public:

        Crab(DisplayObjectContainer* container, int initial_pos_x, int initial_pos_y);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        //add a walk towards the originalXY location? 
        void walk();

        bool collected = false;
        bool touching_button = false;
        int crab_timer = 0;
        int crab_time_max = 500; //how long before the crab moves to its beginning X,Y location
        int walk_speed = 100;
        SDL_Point targetLoc;

        void resolve_collision(DisplayObject *obj);
};
#endif