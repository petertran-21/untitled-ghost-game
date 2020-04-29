#ifndef NPCBUILDER_H
#define NPCCroc_H

#include "MainNPC.h"
#include "SwampTree.h"
#include "Workbench.h"

using namespace std;

class NPCBuilder: public MainNPC{
    
    public:
        NPCBuilder(DisplayObjectContainer* container, DisplayObjectContainer* allSprites);
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);

        bool ability = false;

        void resolve_adjacency(DisplayObject *obj, int status);
};


#endif