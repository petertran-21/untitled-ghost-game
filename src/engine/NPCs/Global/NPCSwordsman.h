#ifndef NPCSWORDSMAN_H
#define NPCSWORDSMAN_H

#include "MainNPC.h"

using namespace std;

class NPCSwordsman : public MainNPC{
    
    public:
        NPCSwordsman();
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
   
};


#endif