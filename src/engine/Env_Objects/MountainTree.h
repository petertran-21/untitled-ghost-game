#ifndef MOUNTAINTREE_H
#define MOUNTAINTREE_H
#define MOUNTAINTREE_SUBTYPE 306

#include "Controller.h"
#include "MainEnvObj.h"


using namespace std;

class MountainTree : public MainEnvObj{
    
    public:
        MountainTree(DisplayObjectContainer* container);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);

        bool mined = false;

};

#endif