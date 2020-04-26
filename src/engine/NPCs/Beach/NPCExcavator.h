#ifndef NPCEXCAVATOR_H
#define NPCEXCAVATOR_H
#define NPCEXCAVATOR_SUBTYPE 19

#include "MainNPC.h"
#include "BreakableWall.h"

using namespace std;

class NPCExcavator : public MainNPC{
    
    public:
        NPCExcavator(DisplayObjectContainer* container, DisplayObjectContainer* allSprites, vector<DisplayObject*> passedInventory);
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);

        void resolve_collision(DisplayObject * obj);
        void resolve_adjacency(DisplayObject * obj, int status);

        bool excavate = false;
};


#endif