#ifndef NPCEXCAVATOR_H
#define NPCEXCAVATOR_H

#include "MainNPC.h"

using namespace std;

class NPCExcavator : public MainNPC{
    
    public:
        NPCExcavator();
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
   
};


#endif