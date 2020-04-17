#ifndef BUTTON_H
#define BUTTON_H

#include "Controller.h"
#include "MainEnvObj.h"


using namespace std;

class Button : public MainEnvObj{
    
    public:
        Button(DisplayObjectContainer* container);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        
        void resolve_collision(DisplayObject *obj);

};

#endif