#ifndef NPCLUMBERJACK_H
#define NPCLUMBERJACK_H

#include "MainNPC.h"
#include "Log.h"

using namespace std;

class NPCLumberjack : public MainNPC{
    
    public:
        NPCLumberjack(DisplayObjectContainer* container, DisplayObjectContainer* allSprites);
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        DisplayObjectContainer* collisionContainer;

        bool chopping = false;

        void resolve_adjacency(DisplayObject *obj, int status);
};


#endif