#ifndef NPCCRAFTSMAN_H
#define NPCCRAFTSMAN_H
#define NPCCRAFTSMAN_SUBTYPE 25

#include "MainNPC.h"
#include "Mineral.h"
#include "CaveLake.h"
#include "Workbench.h"
#include "Bucket.h"
#include "MountainTree.h"

using namespace std;

class NPCCraftsman : public MainNPC{
    
    public:
        NPCCraftsman(DisplayObjectContainer* container, DisplayObjectContainer* allSprites, vector<DisplayObject*> &passedInventory);
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        
        bool ability = false;
        void resolve_collision(DisplayObject *obj);
        void resolve_adjacency(DisplayObject *obj, int status);
};


#endif