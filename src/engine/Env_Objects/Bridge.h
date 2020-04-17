#ifndef BRIDGE_H
#define BRIDGE_H
#define BRIDGE_SUBTYPE 101

#include "Controller.h"
#include "MainEnvObj.h"

#include "Fire.h"
#include "Arrow.h"

using namespace std;

class Bridge : public MainEnvObj{
    
    public:
        Bridge(DisplayObjectContainer* container);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        
        int subtype = 101;
        bool open = false;
        
        void resolve_collision(DisplayObject *obj);

};

#endif