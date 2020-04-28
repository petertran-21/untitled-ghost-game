#ifndef CAVELAKE_H
#define CAVELAKE_H
#define CAVELAKE_SUBTYPE 302

#include "Controller.h"
#include "Mineral.h"


using namespace std;

class CaveLake : public Mineral{
    
    public:
        CaveLake(DisplayObjectContainer* container);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);

};

#endif