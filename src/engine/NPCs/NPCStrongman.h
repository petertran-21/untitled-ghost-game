#ifndef NPCSTRONGMAN_H
#define NPCSTRONGMAN_H

#include "MainNPC.h"

using namespace std;

class NPCStrongman : public MainNPC{
    
    public:
        NPCStrongman();
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
   
};


#endif