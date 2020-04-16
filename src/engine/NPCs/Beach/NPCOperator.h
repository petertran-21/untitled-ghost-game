#ifndef NPCOPERATOR_H
#define NPCOPERATOR_H
#define NPCOPERATOR_SUBTYPE 20

#include "MainNPC.h"

using namespace std;

class NPCOperator : public MainNPC{
    
    public:
        NPCOperator(DisplayObjectContainer* container, DisplayObjectContainer* allSprites);
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        DisplayObjectContainer* collisionContainer;
        void resolve_collision(DisplayObject *obj);
        Valve* current_valve = NULL;
};

#endif