#ifndef NPCVILLAGER_H
#define NPCVILLAGER_H

#include "MainNPC.h"

using namespace std;

class NPCVillager : public MainNPC{
    
    public:
        NPCVillager();
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
   
};


#endif