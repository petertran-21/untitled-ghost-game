#ifndef NPCArcher_H
#define NPCArcher_H
#define NPCARCHER_SUBTYPE 22

#include "MainNPC.h"
#include "Arrow.h"
#include "DisplayObjectContainer.h"

using namespace std;

class NPCArcher : public MainNPC{
    
    public:
        NPCArcher(DisplayObjectContainer* container, DisplayObjectContainer* allSprites, vector<DisplayObject*> &passedInventory);
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        DisplayObjectContainer* collisionContainer;

        void resolve_collision(DisplayObject* obj);
        int subtype = 22;
   
};


#endif