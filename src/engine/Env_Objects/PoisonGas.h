#ifndef POISONGAS_H
#define POISONGAS_H
#define POISONGAS_SUBTYPE 120

#include "Controller.h"
#include "MainEnvObj.h"


using namespace std;

class PoisonGas : public MainEnvObj{
    
    public:
        PoisonGas(DisplayObjectContainer* container);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        
        void resolve_collision(DisplayObject *obj);

};

#endif