#ifndef MINERAL_H
#define MINERAL_H
#define MINERAL_SUBTYPE 301

#include "Controller.h"
#include "MainEnvObj.h"


using namespace std;

class Mineral : public MainEnvObj{
    
    public:
        Mineral(DisplayObjectContainer* container);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);

        bool mined = false;

};

#endif