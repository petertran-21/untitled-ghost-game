#ifndef SIGN_H
#define SIGN_H
#define SIGN_SUBTYPE 304

#include "Controller.h"
#include "MainEnvObj.h"
#include "SceneTrigger.h"

using namespace std;

class Sign : public MainEnvObj{
    
    public:
        Sign(DisplayObjectContainer* container);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);

        bool posted = false;
        SceneTrigger * exit = NULL;
};

#endif