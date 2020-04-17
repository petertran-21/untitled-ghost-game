#ifndef PIT_H
#define PIT_H

#include "Controller.h"
#include "MainEnvObj.h"


using namespace std;

class Pit : public MainEnvObj{
    
    public:
        Pit(DisplayObjectContainer* container);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        
        void resolve_collision(DisplayObject *obj);

};

#endif