#ifndef NPCLUMBERJACK_H
#define NPCLUMBERJACK_H
#define NPCLUMBERJACK_SUBTYPE 21

#include "MainNPC.h"
#include "Log.h"
#include "Bridge.h"

using namespace std;

class NPCLumberjack : public MainNPC{
    
    public:
        NPCLumberjack(DisplayObjectContainer* container, DisplayObjectContainer* allSprites, vector<DisplayObject*> &passedInventory);
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        DisplayObjectContainer* collisionContainer;

        bool chopping = false;

        void resolve_adjacency(DisplayObject *obj, int status);
};


#endif