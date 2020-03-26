#ifndef NPCLUMBERJACK_H
#define NPCLUMBERJACK_H

#include "MainNPC.h"

using namespace std;

class NPCLumberjack : public MainNPC{
    
    public:
        NPCLumberjack();
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
   
};


#endif