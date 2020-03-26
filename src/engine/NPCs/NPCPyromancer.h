#ifndef NPCPYROMANCER_H
#define NPCPYROMANCER_H

#include "MainNPC.h"
#include "Fire.h"

using namespace std;

class NPCPyromancer : public MainNPC{
    
    public:
        NPCPyromancer();
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
   
};


#endif