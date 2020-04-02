#ifndef FIRE_H
#define FIRE_H

#include "Controller.h"
#include "MainNPCObj.h"

#include "Shrub.h"

using namespace std;

class Fire : public MainNPCObj{
    
    public:

        Fire(SDL_Point pos);

        virtual void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        void resolve_collision(DisplayObject *obj);
};
#endif