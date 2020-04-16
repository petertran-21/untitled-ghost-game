#ifndef NPCPYROMANCER_H
#define NPCPYROMANCER_H
#define NPCPYROMANCER_SUBTYPE 451

#include "MainNPC.h"
#include "Fire.h"
#include "DisplayObjectContainer.h"

using namespace std;

class NPCPyromancer : public MainNPC{
    
    public:
        NPCPyromancer(DisplayObjectContainer* container, DisplayObjectContainer* allSprites);
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        DisplayObjectContainer* collisionContainer;
        void resolve_collision(DisplayObject *obj);
};


#endif