#ifndef NPCSTRONGMAN_H
#define NPCSTRONGMAN_H
#define NPCSTRONGMAN_SUBTYPE 26

#include "MainNPC.h"
#include "Sign.h"

using namespace std;

class NPCStrongman : public MainNPC{
    
    public:
        NPCStrongman(DisplayObjectContainer* container, DisplayObjectContainer* allSprites, vector<DisplayObject*> &passedInventory);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        DisplayObjectContainer* collisionContainer;
        
        bool strongmode = false;
        int strongmode_timer = 0;
        int strongmode_timer_max = 20;

        void resolve_adjacency(DisplayObject *obj, int status);

};


#endif