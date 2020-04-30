#ifndef NPCCROC_H
#define NPCCROC_H
#define NPCCROC_SUBTYPE 124

#include "MainNPC.h"

using namespace std;

class NPCCroc: public MainNPC{
    
    public:
        NPCCroc(DisplayObjectContainer* container, DisplayObjectContainer* allSprites, vector<DisplayObject*> &passedInventory);
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        void resolve_collision(DisplayObject * obj);
        bool hitTree = false;
};


#endif