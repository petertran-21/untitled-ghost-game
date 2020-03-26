#ifndef NPCArcher_H
#define NPCArcher_H

#include "MainNPC.h"
#include "Arrow.h"

using namespace std;

class NPCArcher : public MainNPC{
    
    public:
        NPCArcher();
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
   
};


#endif