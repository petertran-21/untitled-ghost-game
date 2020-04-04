#ifndef NPCEXCAVATOR_H
#define NPCEXCAVATOR_H

#include "MainNPC.h"
#include "BreakableWall.h"

using namespace std;

class NPCExcavator : public MainNPC{
    
    public:
        NPCExcavator(DisplayObjectContainer* container, DisplayObjectContainer* allSprites);
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);

        void resolve_collision(DisplayObject * obj);

        bool excavate = false;
};


#endif