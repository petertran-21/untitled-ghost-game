#ifndef NPCCOLLECTOR_H
#define NPCCOLLECTOR_H
#define NPCCOLLECTOR_SUBTYPE 18

#include "MainNPC.h"
#include "Crab.h"

using namespace std;

class NPCCollector : public MainNPC{
    
    public:
        NPCCollector(DisplayObjectContainer* container, DisplayObjectContainer* allSprites);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);

        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        void resolve_collision(DisplayObject* obj);
        Crab *crab = NULL;
        bool can_collect = true;
   
};


#endif