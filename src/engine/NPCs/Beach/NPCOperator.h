#ifndef NPCOPERATOR_H
#define NPCOPERATOR_H

#include "MainNPC.h"

using namespace std;

class NPCOperator : public MainNPC{
    
    public:
        NPCOperator(DisplayObjectContainer* container, DisplayObjectContainer* allSprites);
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        DisplayObjectContainer* collisionContainer;

        bool operated = false;

        void resolve_collision(DisplayObject *obj);
        void resolve_adjacency(DisplayObject *obj, int status);
};

#endif