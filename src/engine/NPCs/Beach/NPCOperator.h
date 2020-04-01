#ifndef NPCOPERATOR_H
#define NPCOPERATOR_H

#include "MainNPC.h"

using namespace std;

class NPCOperator : public MainNPC{
    
    public:
        NPCOperator();
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
   
};


#endif