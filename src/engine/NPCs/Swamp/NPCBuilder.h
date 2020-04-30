#ifndef NPCBUILDER_H
#define NPCCroc_H

#include "MainNPC.h"

using namespace std;

class NPCBuilder: public MainNPC{
    
    public:
        NPCBuilder(DisplayObjectContainer* container, DisplayObjectContainer* allSprites);
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        void resolve_collision(DisplayObject * obj);
};


#endif