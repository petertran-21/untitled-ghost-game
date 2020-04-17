#ifndef NPCVILLAGER_H
#define NPCVILLAGER_H

#include "MainNPC.h"

using namespace std;

class NPCVillager : public MainNPC{
    
    public:
        NPCVillager(DisplayObjectContainer* container, DisplayObjectContainer* allSprites);
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        DisplayObjectContainer* collisionContainer;
        int subtype = 24;
};


#endif