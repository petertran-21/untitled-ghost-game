#ifndef NPCBUILDER_H
#define NPCBUILDER_H
#define NPCBUILDER_SUBTYPE 31

#include "MainNPC.h"
#include "Workbench.h"
#include "SwampBridge.h"

using namespace std;

class NPCBuilder: public MainNPC{
    
    public:
        NPCBuilder(DisplayObjectContainer* container, DisplayObjectContainer* allSprites, vector<DisplayObject*> &passedInventory);
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);

        bool ability = false;

        void resolve_adjacency(DisplayObject *obj, int status);
};


#endif