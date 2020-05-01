#ifndef FALLENTREE_H
#define FALLENTREE_H
#define FALLENTREE_SUBTYPE 307

#include "Controller.h"
#include "MainEnvObj.h"


using namespace std;

class FallenTree : public MainEnvObj{
    
    public:
        FallenTree(DisplayObjectContainer* container);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        
        bool destroyed = false;

};

#endif