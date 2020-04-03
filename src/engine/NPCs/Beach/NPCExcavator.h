#ifndef NPCEXCAVATOR_H
#define NPCEXCAVATOR_H

#include "MainNPC.h"

using namespace std;

class NPCExcavator : public MainNPC{
    
    public:
        NPCExcavator(DisplayObjectContainer* container, DisplayObjectContainer* allSprites);
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        DisplayObjectContainer* collisionContainer;
};


#endif