#ifndef NPCFISHERMAN_H
#define NPCFISHERMAN_H

#include "MainNPC.h"

using namespace std;

class NPCFisherman : public MainNPC{
    
    public:
        NPCFisherman();
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
   
};


#endif