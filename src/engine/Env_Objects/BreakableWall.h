#ifndef BREAKABLEWALL_H
#define BREAKABLEWALL_H
#define BREAKABLEWALL_SUBTYPE 10

#include "Controller.h"
#include "MainEnvObj.h"


using namespace std;

class BreakableWall : public MainEnvObj{
    
    public:
        BreakableWall(DisplayObjectContainer* container);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);

        bool broken = false;

        void resolve_collision(DisplayObject *obj);
        int getSubtype(){return this->subtype;};

};

#endif