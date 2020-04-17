#ifndef BRIDGE_H
#define BRIDGE_H

#include "Controller.h"
#include "MainEnvObj.h"


using namespace std;

class Rock : public MainEnvObj{
    
    public:
        Rock(DisplayObjectContainer* container);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        
        void resolve_collision(DisplayObject *obj);

};

#endif