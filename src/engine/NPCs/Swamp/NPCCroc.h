#ifndef NPCCROC_H
#define NPCCROC_H

#include "MainNPC.h"

using namespace std;

class NPCCroc: public MainNPC{
    
    public:
        NPCCroc(DisplayObjectContainer* container, DisplayObjectContainer* allSprites);
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        DisplayObjectContainer* collisionContainer;
};


#endif