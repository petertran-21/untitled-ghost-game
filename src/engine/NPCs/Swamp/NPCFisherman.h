#ifndef NPCFISHERMAN_H
#define NPCFISHERMAN_H
#define NPCFISHERMAN_SUBTYPE 28

#include "MainNPC.h"

using namespace std;

class NPCFisherman : public MainNPC{
    
    public:
        NPCFisherman(DisplayObjectContainer* container, DisplayObjectContainer* allSprites, vector<DisplayObject*> &passedInventory);
        void resolve_collision(DisplayObject * obj);
        void resolve_adjacency (DisplayObject* obj, int status);
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);

        bool hasBoat = false;
        bool hitBoat = false;
        bool offBoat = true;
};


#endif