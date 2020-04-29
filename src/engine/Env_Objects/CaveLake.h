#ifndef CAVELAKE_H
#define CAVELAKE_H
#define CAVELAKE_SUBTYPE 302

#include "Controller.h"
#include "MainEnvObj.h"


using namespace std;

class CaveLake : public MainEnvObj{
    
    public:
        CaveLake(DisplayObjectContainer* container);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);

        bool mined = false;
};

#endif