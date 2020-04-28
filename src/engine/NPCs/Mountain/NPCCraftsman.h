#ifndef NPCCRAFTSMAN_H
#define NPCCRAFTSMAN_H
#define NPCCRAFTSMAN_SUBTYPE 25

#include "MainNPC.h"
#include "Mineral.h"

using namespace std;

class NPCCraftsman : public MainNPC{
    
    public:
        NPCCraftsman(DisplayObjectContainer* container, DisplayObjectContainer* allSprites);
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        DisplayObjectContainer* collisionContainer;

        bool ability = false;

        void resolve_adjacency(DisplayObject *obj, int status);
};


#endif