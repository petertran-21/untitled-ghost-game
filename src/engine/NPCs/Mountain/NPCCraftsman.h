#ifndef NPCArcher_H
#define NPCArcher_H

#include "MainNPC.h"
#include "Arrow.h"

using namespace std;

class NPCCraftsman : public MainNPC{
    
    public:
        NPCCraftsman();
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
   
};


#endif