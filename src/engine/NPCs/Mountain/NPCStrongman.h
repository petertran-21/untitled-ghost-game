#ifndef NPCSTRONGMAN_H
#define NPCSTRONGMAN_H
#define NPCSTRONGMAN_SUBTYPE 26

#include "MainNPC.h"

using namespace std;

class NPCStrongman : public MainNPC{
    
    public:
        NPCStrongman(DisplayObjectContainer* container, DisplayObjectContainer* allSprites);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        DisplayObjectContainer* collisionContainer;
        
        bool strongmode = false;
        int strongmode_timer = 0;
        int strongmode_timer_max = 20;

};


#endif