#ifndef NPCDOCTOR_H
#define NPCDOCTOR_H

#include "MainNPC.h"

using namespace std;

class NPCDoctor: public MainNPC{
    
    public:
        NPCDoctor();
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
   
};


#endif