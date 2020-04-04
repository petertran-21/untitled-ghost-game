#ifndef NPCArcher_H
#define NPCArcher_H

#include "MainNPC.h"
#include "Arrow.h"
#include "DisplayObjectContainer.h"

using namespace std;

class NPCArcher : public MainNPC{
    
    public:
        NPCArcher(DisplayObjectContainer* container, DisplayObjectContainer* allSprites);
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        DisplayObjectContainer* collisionContainer;

        void resolve_collision(DisplayObject* obj);
   
};


#endif